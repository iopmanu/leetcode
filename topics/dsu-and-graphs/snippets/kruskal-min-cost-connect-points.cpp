    int minCostConnectPoints(vector<vector<int>>& points) {
        int V = points.size();
        if (V <= 1) return 0;

        std::vector<std::vector<int>> edges{};
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int dist = std::abs(points[i][0] - points[j][0]) + std::abs(points[i][1] - points[j][1]);
                edges.push_back({dist, i, j});
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