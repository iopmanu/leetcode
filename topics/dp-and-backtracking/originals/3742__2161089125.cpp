class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(m, vector<int>(k + 1, -2)));
        auto dfs = [&](auto& self, int i, int j, int balance) -> int {
            if (i >= n || j >= m) {
                return INT_MIN;
            }

            int score = 0;
            if (grid[i][j] == 1) {
                score = 1;
                balance--;
            } else if (grid[i][j] == 2) {
                score = 2;
                balance--;
            }

            if (balance < 0) {
                return INT_MIN;
            }

            if (i == n - 1 && j == m - 1) {
                return score;
            }

            if (memo[i][j][balance] != -2) {
                return memo[i][j][balance];
            }

            int nextBest = std::max(self(self, i + 1, j, balance), self(self, i, j + 1, balance));

            memo[i][j][balance] = (nextBest == INT_MIN) ? INT_MIN : score + nextBest;
            return memo[i][j][balance];
        };

        int score = dfs(dfs, 0, 0, k);
        return score < 0 ? -1 : score;
    }
};
