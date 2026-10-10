class Solution {
    struct DSU {
        std::vector<int> parent{};
        std::vector<int> size{};

        DSU(int n) {
            parent.resize(n);
            size.resize(n, 1);

            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        void uni(int i, int j) {
            int parentI = find(i);
            int parentJ = find(j);

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

        int find(int i) {
            if (parent[i] == i) {
                return i;
            }

            return parent[i] = find(parent[i]);
        }
    };

public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        std::vector<std::vector<int>> sorted = edges;
        for (int i = 0; i < sorted.size(); i++) {
            sorted[i].push_back(i);
        }
        std::sort(sorted.begin(), sorted.end(), [](auto &l, auto& r) {
            return l[2] < r[2];
        });
        
        
        std::function<int(int, int)> buildMstWithSkip = [&](int skip, int force) {
            int cost = 0;
            DSU dsu(n);
            int count = 0;

            if (force >= 0) {
                cost += edges[force][2];
                dsu.uni(edges[force][0], edges[force][1]);
                ++count;
            }

            for (auto&& e : sorted) {
                if (e[3] == skip || e[3] == force) {
                    continue;
                }

                if (dsu.find(e[0]) != dsu.find(e[1])) {
                    dsu.uni(e[0], e[1]);
                    cost += e[2];
                    ++count;
                }
            }

            if (count != n - 1) {
                return INT_MAX;
            }

            return cost;
        };

        int mstScore = buildMstWithSkip(-1, -1);

        std::vector<std::vector<int>> result(2, std::vector<int>{});
        for (int i = 0; i < edges.size(); i++) {
            int criticalScore = buildMstWithSkip(i, -1);
            int pseudoCriticalScore = buildMstWithSkip(-1, i);

            if (criticalScore > mstScore) {
                result[0].push_back(i);
            } else if (pseudoCriticalScore == mstScore) {
                result[1].push_back(i);
            }
        }

        return result;
    }
};