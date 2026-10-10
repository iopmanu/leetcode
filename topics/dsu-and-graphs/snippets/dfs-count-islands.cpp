    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(); int m = grid[0].size();
        std::vector<std::pair<int, int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= n) {
                return;
            }

            if (j < 0 || j >= m) {
                return;
            }

            if (grid[i][j] == '0') {
                return;
            }

            grid[i][j] = '0';

            for (auto [dx, dy] : dir) {
                int newX = i + dx; int newY = j + dy;
                dfs(newX, newY);
            }
        };

        int result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1') {
                    ++result;
                    dfs(i, j);
                }
            }
        }

        return result;
    }