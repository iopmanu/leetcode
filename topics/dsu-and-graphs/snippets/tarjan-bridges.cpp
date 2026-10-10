class Solution {
    std::vector<int> disc;
    std::vector<int> low;
    std::vector<int> parent;
    std::vector<std::vector<int>> adj{};
    int time = 0;

    void tarjan(int n, std::vector<std::vector<int>>& bridges) {
        std::function<void(int)> dfs = [&](int v) {
            disc[v] = low[v] = time++;

            for (int neighbor : adj[v]) {
                if (disc[neighbor] == -1) {
                    parent[neighbor] = v;
                    
                    dfs(neighbor);

                    low[v] = std::min(low[neighbor], low[v]);

                    if (low[neighbor] > disc[v]) {
                        bridges.push_back({v, neighbor});
                    }
                } else if (neighbor != parent[v]) {
                    low[v] = std::min(low[v], disc[neighbor]);
                }
            }
        };

        for (int v = 0; v < n; v++) {
            if (disc[v] == -1) {
                dfs(v);
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        adj.resize(n, std::vector<int>{});
        disc.resize(n, -1); low.resize(n, -1);
        parent.resize(n, -1);
        for (auto&& edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        std::vector<std::vector<int>> bridges{};
        tarjan(n, bridges);
        return bridges;
    }
};