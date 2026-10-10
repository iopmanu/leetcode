class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj{};

        auto addEdge = [&](int u, int v) {
            adj[u].push_back(std::make_pair(scores[v], v));
            std::sort(adj[u].rbegin(), adj[u].rend());
            if (adj[u].size() > 3) {
                adj[u].pop_back();
            }
        };

        for (auto& e : edges) {
            addEdge(e[0], e[1]);
            addEdge(e[1], e[0]);
        }

        // a -> b -> c -> d
        int score = -1;
        for (auto& e : edges) {
            int b = e[0]; int c = e[1];
            for (auto&& [_, a] : adj[b]) {
                for (auto&& [_, d] : adj[c]) {
                    if (a != c && b != d && a != d) {
                        score = std::max(score, scores[a] + scores[b] + scores[c] + scores[d]);
                    }
                }
            }
        }

        return score;
    }
};