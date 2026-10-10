    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj{};
        for (auto&& time : times) {
            adj[time[0]].push_back(std::make_pair(time[1], time[2]));
        }

        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<>> pq{};
        std::unordered_set<int> visited;
        pq.push({0, k});

        int result = INT_MIN;
        while (!pq.empty()) {
            int path = pq.top()[0]; int v = pq.top()[1];
            pq.pop();
            if (visited.contains(v)) {
                continue;
            }

            visited.insert(v);
            result = std::max(path, result);

            for (auto [neighbor, weight] : adj[v]) {
                if (!visited.contains(neighbor)) {
                    pq.push({path + weight, neighbor});
                }
            }
        }

        return visited.size() == n ? result : -1;
    }
