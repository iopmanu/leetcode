    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        std::unordered_map<int, std::vector<int>> adj{};
        for (auto&& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int k = 2;
        std::vector<std::vector<int>> dist(n + 1, std::vector<int>(k, INT_MAX));
        
        std::deque<std::vector<int>> pq{};
        pq.push_back({0, 1});
        dist[1][0] = 0;

        while (!pq.empty()) {
            int v = pq.front()[1]; int currentTime = pq.front()[0];
            pq.pop_front();

            if (currentTime > dist[v][1]) {
                continue;
            }

            if ((currentTime / change) % 2 == 1) {
                currentTime = (currentTime / change + 1) * change;
            }

            int nextTime = currentTime + time;

            for (int dst : adj[v]) {
                if (nextTime < dist[dst][0]) {
                    dist[dst][1] = dist[dst][0];
                    dist[dst][0] = nextTime;
                    pq.push_back({nextTime, dst});
                } else if (nextTime > dist[dst][0] && nextTime < dist[dst][1]) {
                    dist[dst][1] = nextTime;
                    pq.push_back({nextTime, dst});
                }
            }
        }

        return dist[n][1];
    }
