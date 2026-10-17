class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        std::unordered_map<int, std::unordered_set<int>> rows{};
        std::unordered_map<int, std::unordered_set<int>> cols{};
        std::unordered_map<int, std::unordered_set<int>> squares{};

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    continue;
                }
                
                if (rows[i].contains(board[i][j])) {
                    return false;
                }

                if (cols[j].contains(board[i][j])) {
                    return false;
                }

                int square = (i / 3) * 3 + j / 3;
                if (squares[square].contains(board[i][j])) {
                    return false;
                }

                squares[square].insert(board[i][j]);
                cols[j].insert(board[i][j]);
                rows[i].insert(board[i][j]);
            }
        }

        return true;
    }
};