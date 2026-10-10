#include <vector>
#include <functional>

class Solution {
    struct DSU {
        std::vector<int> parent;
        std::vector<int> size;

        DSU(int n) {
            parent.resize(n);
            size.resize(n, 1);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        void uni(int i, int j) {
            int rootI = find(i);
            int rootJ = find(j);
            if (rootI == rootJ) {
                return;
            }

            if (size[rootI] > size[rootJ]) {
                size[rootI] += size[rootJ];
                parent[rootJ] = rootI;
            } else {
                size[rootJ] += size[rootI];
                parent[rootI] = rootJ;
            }
        }

        int find(int i) {
            if (i == parent[i]) {
                return i;
            }

            return parent[i] = find(parent[i]);
        }
    };

public:
    int latestDayToCross(int row, int col, std::vector<std::vector<int>>& cells) {
        std::vector<std::vector<int>> grid(row, std::vector<int>(col, 0));
        for (auto&& cell : cells) {
            grid[cell[0] - 1][cell[1] - 1] = 1;
        }

        DSU dsu(row * col + 2);
        std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || j < 0 || i >= row || j >= col || grid[i][j] != 0) {
                return;
            }

            grid[i][j] = 2;

            for (auto&& d : dirs) {
                int newI = i + d.first; int newJ = j + d.second;
                if (newI >= 0 && newJ >= 0 && newI < row && newJ < col && grid[newI][newJ] == 0) {
                    dsu.uni(i * col + j + 1, newI * col + newJ + 1);
                }
            }

            for (auto&& d : dirs) {
                dfs(i + d.first, j + d.second);
            }
        };

        for (int j = 0; j < col; j++) {
            if (grid[0][j] == 0) {
                dfs(0, j);
                dsu.uni(0, j + 1);
            }
        }

        for (int j = 0; j < col; j++) {
            if (grid[row - 1][j] == 2) {
                dsu.uni(row * col + 1, (row - 1) * col + j + 1);
            }
        }

        if (dsu.find(0) == dsu.find(row * col + 1)) {
            return cells.size();
        }

        for (int d = cells.size() - 1; d >= 0; --d) {
            int i = cells[d][0] - 1; int j = cells[d][1] - 1;
            grid[i][j] = 0;

            if (i == 0) {
                dsu.uni(0, i * col + j + 1);
            }
            if (i == row - 1) {
                dsu.uni(row * col + 1, i * col + j + 1);
            }

            for (auto&& dir : dirs) {
                int newI = i + dir.first; int newJ = j + dir.second;
                if (newI >= 0 && newJ >= 0 && newI < row && newJ < col && grid[newI][newJ] != 1) {
                    dsu.uni(i * col + j + 1, newI * col + newJ + 1);
                }
            }

            if (i == 0 || grid[i][j] == 0) {
                bool hasComponent = false;
                if (i == 0) hasComponent = true;
                
                for (auto&& dir : dirs) {
                    int newI = i + dir.first; int newJ = j + dir.second;
                    if (newI >= 0 && newJ >= 0 && newI < row && newJ < col && grid[newI][newJ] == 2) {
                        hasComponent = true;
                        break;
                    }
                }

                if (hasComponent) {
                    dfs(i, j);
                }
            }

            if (dsu.find(0) == dsu.find(row * col + 1)) {
                return d;
            }
        }

        return -1;
    }
};
