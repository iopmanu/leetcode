class Solution {
    struct UnionFind {
        std::vector<int> parent{};
        std::vector<int> size{};

        UnionFind(int V) {
            parent.resize(V);
            size.resize(V, 1);

            for (int i = 0; i < V; i++) {
                parent[i] = i;
            }
        }

        void unify(int i, int j) {
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

        int query(int i) {
            int p = parent[i];
            if (i == p) {
                return i;
            }

            return parent[i] = query(p);
        }

    };
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int V = 0;
        std::unordered_map<uint64_t, int> enumerate{};
        for (auto&& point : points) {
            enumerate[key(point)] = V++;
        }
        
        std::vector<std::vector<int>> edges{};
        for (auto&& l : points) {
            for (auto&& r : points) {
                int dist = std::abs(l[0] - r[0]) + std::abs(l[1] - r[1]);
                edges.push_back({dist, enumerate[key(l)], enumerate[key(r)]});
            }
        }

        std::sort(edges.begin(), edges.end());

        UnionFind uf(V);
        int visited = 0; int cost = 0;
        for (auto&& e : edges) {
            if (uf.query(e[1]) != uf.query(e[2])) {
                uf.unify(e[1], e[2]);
                cost += e[0];

                if (++visited == V - 1) {
                    return cost;
                }
            }
        }

        return 0;
    }

    uint64_t key(std::vector<int>& point) {
        uint64_t x = static_cast<uint32_t>(point[0]);
        uint64_t y = static_cast<uint32_t>(point[1]);
        return (x << 32) | y;
    }

};