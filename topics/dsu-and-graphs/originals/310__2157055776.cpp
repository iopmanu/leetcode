class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }

        std::vector<std::vector<int>> adj(n, std::vector<int>());
        std::vector<int> degree(n, 0);
        for (auto&& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            ++degree[e[0]];
            ++degree[e[1]];
        }

        std::deque<int> leaves{};
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                leaves.push_back(i);
            }
        }

        int remaining = n;
        while (remaining > 2) {
            int size = leaves.size();
            for (int i = 0; i < size; i++) {
                int leaf = leaves.front(); leaves.pop_front();
                for (int neighbor : adj[leaf]) {
                    degree[neighbor]--;

                    if (degree[neighbor] == 1) {
                        leaves.push_back(neighbor);
                    }
                }
            }

            remaining -= size;
        }

        return {leaves.begin(), leaves.end()};
    }
};