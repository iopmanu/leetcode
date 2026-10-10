class Solution {
    struct UnionFind {
        std::vector<int> parent{};

        UnionFind(int size) {
            parent.resize(size);
            for (int i = 0; i < parent.size(); i++) {
                parent[i] = i;
            }
        }

        int find(int i) {
            if (parent[i] == i) {
                return i;
            }

            return find(parent[i]);
        }

        void unite(int i, int j) {
            int iparent = find(i);
            int jparent = find(j);

            parent[iparent] = jparent;
        }
    };

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        auto uf = UnionFind(n + 1);
        for (auto&& edge : edges) {
            if (uf.find(edge[0]) == uf.find(edge[1])) {
                return edge;
            }

            uf.unite(edge[0], edge[1]);
        }

        return {};
    }
};