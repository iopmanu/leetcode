    void solve(vector<vector<char>>& board) {
        int n = board.size(); int m = board[0].size();
        std::vector<std::pair<int, int>> dirs{{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || j < 0 || i >= n || j >= m) {
                return;
            }

            if (board[i][j] == 'V' || board[i][j] == 'X') {
                return;
            }

            board[i][j] = 'V';
            for (auto [di, dj] : dirs) {
                dfs(i + di, j + dj);
            }
        };

        for (int i = 0; i < n; i++) {
            dfs(i, 0);
            dfs(i, m - 1);
        }

        for (int j = 0; j < m; j++) {
            dfs(0, j);
            dfs(n - 1, j);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'V') {
                    board[i][j] = 'O';
                }
            }
        }
    }