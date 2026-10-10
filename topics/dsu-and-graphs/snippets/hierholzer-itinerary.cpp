    vector<string> findItinerary(vector<vector<string>>& tickets) {
        std::unordered_map<std::string, std::vector<std::string>> adj{};

        for (auto&& ticket : tickets) {
            adj[ticket[0]].push_back(ticket[1]);
        }

        for (auto&& [_, dest] : adj) {
            std::sort(dest.rbegin(), dest.rend());
        }

        std::vector<std::string> path{};
        std::function<void(const std::string& current)> dfs = [&](const std::string& src) {
            while (!adj[src].empty()) {
                std::string next = adj[src].back();
                adj[src].pop_back();
                dfs(next);
            }

            path.push_back(src);
        };

        dfs("JFK");
        std::reverse(path.begin(), path.end());

        return path;
    }
