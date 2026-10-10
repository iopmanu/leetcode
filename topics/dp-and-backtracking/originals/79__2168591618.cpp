class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(); int m = board[0].size();

        std::function<bool(int, int, int)> dfs = [&](int i, int j, int ptr) {
            if (ptr >= word.size()) {
                return true;
            }

            if (i < 0 || j < 0 || i >= n || j >= m) {
                return false;
            }

            uint64_t key = (uint64_t(i) << 32) | uint64_t(j);
            if (board[i][j] == '#' || board[i][j] != word[ptr]) {
                return false;
            }

            auto tmp = board[i][j];
            board[i][j] = '#';
            bool result = dfs(i + 1, j, ptr + 1) | dfs(i - 1, j, ptr + 1)
                        | dfs(i, j + 1, ptr + 1) | dfs(i, j - 1, ptr + 1);
            board[i][j] = tmp;

            return result;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dfs(i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};