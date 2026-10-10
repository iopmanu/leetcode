class Solution {
    struct UnionFind {
        std::vector<int> parent{};
        std::vector<int> size{};

        UnionFind(int n) {
            size.resize(n, 1);
            parent.resize(n);
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

        void uni(int i, int j) {
            int parentI = query(i);
            int parentJ = query(j);

            if (parentI == parentJ) {
                return;
            }

            if (size[parentI] > size[parentJ]) {
                size[parentI] += size[parentJ];
                parent[parentJ] = parentI;
            } else {
                size[parentJ] += size[parentI];
                parent[parentI] = parentJ;
            }
        }

        int sz(int i) {
            return size[query(i)];
        }
    };

public:
    vector<int> hitBricks(vector<vector<int>>& grid, vector<vector<int>>& hits) {
        int rows = grid.size(); int cols = grid[0].size();

        std::vector<std::vector<int>> broken = grid;
        for (auto&& h : hits) {
            broken[h[0]][h[1]] = 0;
        }

        auto outOfBound = [&](int i, int j) {
            return i < 0 || j < 0 || i >= rows || j >= cols;
        };

        std::vector<std::vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int roofNode = rows * cols;
        UnionFind uf(rows * cols + 1);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (broken[i][j]) {
                    if (i == 0) {
                        uf.uni(i * cols + j, roofNode);
                    }

                    for (auto&& d : dirs) {
                        int newI = i + d[0]; int newJ = j + d[1];
                        if (!outOfBound(newI, newJ) && broken[newI][newJ]) {
                            uf.uni(i * cols + j, newI * cols + newJ);
                        }
                    }
                }
            }
        }

        std::vector<int> result(hits.size(), 0);

        for (int i = hits.size() - 1; i >= 0; i--) {
            int x = hits[i][0]; int y = hits[i][1];
            if (!grid[x][y]) {
                continue;
            }

            int current = uf.sz(roofNode);
            if (x == 0) {
                uf.uni(x * cols + y, roofNode);
            } 

            for (auto&& d : dirs) {
                int newI = x + d[0]; int newJ = y + d[1];
                if (!outOfBound(newI, newJ) && broken[newI][newJ]) {
                    uf.uni(x * cols + y, newI * cols + newJ);
                }
            }

            broken[x][y] = 1;

            int restored = uf.sz(roofNode);
            result[i] = std::max(restored - current - 1, 0);
        }

        return result;
    }
};