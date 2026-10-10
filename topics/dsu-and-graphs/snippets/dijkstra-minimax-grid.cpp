    int swimInWater(vector<vector<int>>& grid) {
        int r = grid.size(); int c = grid[0].size();

        std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<>> pq{};
        pq.push({grid[0][0], 0, 0});

        std::unordered_set<int> visited{};
        while (!pq.empty()) {
            int i = pq.top()[1]; int j = pq.top()[2];
            int time = pq.top()[0];
            pq.pop();
            
            if (visited.contains(i * r + j)) {
                continue;
            }

            if (i == r - 1 && j == c - 1) {
                return time;
            }

            visited.insert(i * r + j);

            for (auto&& d : directions) {
                int newI = i + d[0]; int newJ = j + d[1];
                if (newI < 0 || newJ < 0 || newI >= r || newJ >= c) {
                    continue;
                }

                if (visited.contains(newI * r + newJ)) {
                    continue;
                }

                int nextTime = std::max(grid[newI][newJ], time);
                pq.push({nextTime, newI, newJ});
            }
        }

        return -1;
    }
