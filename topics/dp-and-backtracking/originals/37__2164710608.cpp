class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        std::vector<std::unordered_set<char>> rows(9, std::unordered_set<char>{});
        std::vector<std::unordered_set<char>> cols(9, std::unordered_set<char>{});
        std::vector<std::unordered_set<char>> quads(9, std::unordered_set<char>{});

        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] != '.') {
                    char val = board[r][c];
                    rows[r].insert(val);
                    cols[c].insert(val);
                    quads[(r / 3) * 3 + c / 3].insert(val);
                }
            }
        }

        std::function<bool(int, int)> recursive = [&](int i, int j) {
            if (j == 9) {
                ++i; j = 0;
            }

            if (i == 9) {
                return true;
            }

            if (board[i][j] != '.') {
                return recursive(i, j + 1);
            }

            bool result = false;
            for (int digit = '1'; digit <= '9'; ++digit) {
                if (rows[i].contains(digit) || cols[j].contains(digit)) {
                    continue;
                }

                int quadIdx = (i / 3) * 3 + j / 3;
                if (quads[quadIdx].contains(digit)) {
                    continue;
                }

                board[i][j] = digit;

                rows[i].insert(digit);
                cols[j].insert(digit);
                quads[quadIdx].insert(digit);

                if (recursive(i, j + 1)) {
                    return true;
                }

                board[i][j] = '.';
                rows[i].erase(digit);
                cols[j].erase(digit);
                quads[quadIdx].erase(digit);
            }

            return result;
        };

        recursive(0, 0);
    }
};