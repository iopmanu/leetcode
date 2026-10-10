#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
    struct UnionFind {
        std::vector<int> parent{};
        std::vector<int> size{};
        int maxSize = 0;

        UnionFind(int n) {
            parent.resize(n);
            size.resize(n, 1);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            } 
        }

        int query(int i) {
            if (parent[i] == i) {
                return i;
            }
            return parent[i] = query(parent[i]);
        }

        int querySize(int i) {
            return size[query(i)];
        }

        void uni(int l, int r) {
            int lParent = query(l);
            int rParent = query(r);

            if (lParent == rParent) {
                return;
            }

            if (size[lParent] > size[rParent]) {
                size[lParent] += size[rParent];
                maxSize = std::max(size[lParent], maxSize);
                parent[rParent] = lParent;
            } else {
                size[rParent] += size[lParent];
                maxSize = std::max(size[rParent], maxSize);
                parent[lParent] = rParent;
            }
        }

        int getMaxSize() {
            return maxSize;
        }
    };

public:
    int largestIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int n = rows * cols;

        std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::unordered_set<int> visited{};
        UnionFind uf(n);

        std::function<void(int, int, int)> dfs = [&](int i, int j, int parentKey) {
            if (i < 0 || j < 0 || i >= rows || j >= cols) {
                return;
            }
            if (grid[i][j] == 0) {
                return;
            }

            int key = i * cols + j;
            if (visited.contains(key)) {
                return;
            }

            visited.insert(key);
            uf.uni(parentKey, key);

            for (auto&& d : dirs) {
                dfs(i + d[0], j + d[1], parentKey);
            }
        };

        bool hasLand = false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int key = i * cols + j;
                if (grid[i][j] && !visited.contains(key)) {
                    hasLand = true;
                    uf.maxSize = std::max(uf.maxSize, 1);
                    dfs(i, j, key);
                }
            }
        }

        if (!hasLand) {
            return 1;
        }

        int result = uf.getMaxSize();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 0) {
                    std::unordered_set<int> uniqueRoots;
                    
                    for (auto&& d : dirs) {
                        int newI = i + d[0]; 
                        int newJ = j + d[1];
                        
                        if (newI >= 0 && newJ >= 0 && newI < rows && newJ < cols && grid[newI][newJ] == 1) {
                            int newKey = newI * cols + newJ;
                            uniqueRoots.insert(uf.query(newKey));
                        }
                    }

                    int unionSize = 1;
                    for (int root : uniqueRoots) {
                        unionSize += uf.size[root];
                    }

                    result = std::max(unionSize, result);
                }
            }
        }

        return std::max(result, uf.getMaxSize());
    }
};
