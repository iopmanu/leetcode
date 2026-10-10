    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(); int m = grid[0].size();
        std::vector<std::pair<int, int>> dir{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::function<int(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= n) {
                return 0;
            }

            if (j < 0 || j >= m) {
                return 0;
            }

            if (grid[i][j] == 0) {
                return 0;
            }
            
            grid[i][j] = 0;

            int current = 1;
            for (auto [dx, dy] : dir) {
                int newX = i + dx; int newY = j + dy;
                current += dfs(newX, newY);
            }

            return current;
        };

        int result = INT_MIN;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]) {
                    result = std::max(dfs(i, j), result);
                }
            }
        }

        return result == INT_MIN ? 0 : result;
    }