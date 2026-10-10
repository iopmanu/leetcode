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

        void unite(int i, int j) {
            int parentI = query(i);
            int parentJ = query(j);

            if (parentI == parentJ) {
                return;
            }

            if (size[parentI] >= size[parentJ]) {
                size[parentI] += size[parentJ];
                parent[parentJ] = parentI;
            } else {
                size[parentJ] += size[parentI];
                parent[parentI] = parentJ;
            }
        }
    };

public:
    int swimInWater(vector<vector<int>>& grid) {
        int r = grid.size(); int c = grid[0].size();
        if (r == 1 && c == 1) {
            return grid[0][0];
        }

        std::vector<std::vector<int>> edges{};
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (i > 0) {
                    edges.push_back({std::max(grid[i][j], grid[i - 1][j]), i * c + j, (i - 1) * c + j});
                }

                if (j > 0) {
                    edges.push_back({std::max(grid[i][j], grid[i][j - 1]), i * c + j, i * c + j - 1});
                }
            }
        }

        std::sort(edges.begin(), edges.end());

        UnionFind uf(r * c + 1);
        for (auto&& e : edges) {
            uf.unite(e[1], e[2]);
            if (uf.query(0) == uf.query(r * c - 1)) {
                return e[0];
            }
        }

        return -1;
    }
};