    vector<vector<string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> result{};
        std::vector<std::string> board(n, std::string(n, '.'));

        std::function<bool(int, int)> valid = [&](int i, int j) {
            int row = i - 1; int col = j - 1;
            while (row >= 0 && col >= 0) {
                if (board[row--][col--] == 'Q') {
                    return false;
                }
            }

            row = i - 1; col = j;
            while (row >= 0) {
                if (board[row--][col] == 'Q') {
                    return false;
                }
            }

            row = i - 1; col = j + 1;
            
            while (row >= 0 && col <= n) {
                if (board[row--][col++] == 'Q') {
                    return false;
                }
            }

            return true;
        };
        
        std::function<void(int, int)> recursive = [&](int i, int j) {
            if (i == n) {
                result.push_back(board);
                return;
            }

            for (int j = 0; j < n; j++) {
                if (valid(i, j)) {
                    board[i][j] = 'Q';
                    recursive(i + 1, j);
                    board[i][j] = '.';
                }
            }
        };

        recursive(0, 0);
        return result;
    }
