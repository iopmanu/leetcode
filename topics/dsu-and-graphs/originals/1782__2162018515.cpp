class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        std::vector<int> ranks(n + 1, 0); 
        std::vector<int> sorted(n + 1, 0);

        std::vector<std::unordered_map<int, int>> shared(n + 1);
        for (auto& e : edges) {
            sorted[e[0]] = ranks[e[0]] = ranks[e[0]] + 1;
            sorted[e[1]] = ranks[e[1]] = ranks[e[1]] + 1;
            shared[std::min(e[0], e[1])][std::max(e[0], e[1])]++;
        }

        std::sort(sorted.begin(), sorted.end());

        std::vector<int> result{};
        for (auto&& q : queries) {
            int res = 0;
            for (int u = 1, v = n; u < v;) {
                if (q < sorted[u] + sorted[v]) {
                    res += (v--) - u;
                } else {
                    ++u;
                }
            }

            for (int u = 1; u <= n; u++) {
                for (auto [v, sharedCount] : shared[u]) {
                    if (q < ranks[u] + ranks[v] && q + sharedCount >= ranks[u] + ranks[v]) {
                        --res;
                    }
                }
            }

            result.push_back(res);
        }

        return result;
    }
};