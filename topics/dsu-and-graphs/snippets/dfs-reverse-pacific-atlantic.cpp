    std::vector<std::vector<int>> pacificAtlantic(
        std::vector<std::vector<int>>& heights
    ) {
        if (heights.empty() || heights[0].empty()) {
            return {};
        }

        int n = heights.size();
        int m = heights[0].size();

        std::vector<std::vector<int>> canFlow(
            n, std::vector<int>(m, 0)
        );

        std::vector<std::pair<int, int>> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        int PACIFIC = 1 << 1;
        int ATLANTIC = 1 << 2;
        int BOTH = PACIFIC | ATLANTIC;

        std::vector<std::vector<int>> result;

        std::function<void(int, int, int)> dfs =
            [&](int i, int j, int from) {

            if (canFlow[i][j] & from) {
                return;
            }

            canFlow[i][j] |= from;

            if ((canFlow[i][j] & BOTH) == BOTH) {
                result.push_back({i, j});
            }

            for (auto [dx, dy] : directions) {
                int newX = i + dx;
                int newY = j + dy;

                if (
                    newX >= 0 && newX < n &&
                    newY >= 0 && newY < m &&
                    heights[newX][newY] >= heights[i][j]
                ) {
                    dfs(newX, newY, from);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            dfs(i, 0, PACIFIC);
        }

        for (int j = 0; j < m; ++j) {
            dfs(0, j, PACIFIC);
        }

        for (int i = 0; i < n; ++i) {
            dfs(i, m - 1, ATLANTIC);
        }

        for (int j = 0; j < m; ++j) {
            dfs(n - 1, j, ATLANTIC);
        }

        return result;
    }