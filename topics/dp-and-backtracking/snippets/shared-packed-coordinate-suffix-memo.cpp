class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size(); int m = matrix[0].size();
        std::unordered_map<uint64_t, int> memo{};

        std::function<int(int, int)> recursive = [&](int i, int j) -> int {
            if (i < 0 || j < 0 || j >= m || i >= n) {
                return 1e7;
            }

            if (i == n - 1) {
                return matrix[i][j];
            }

            uint64_t key = (uint64_t(i) << 32) | uint64_t(j);
            if (memo.contains(key)) {
                return memo[key];
            }

            int minPath = std::min({
                recursive(i + 1, j), 
                recursive(i + 1, j - 1), 
                recursive(i + 1, j + 1)
            });

            return memo[key] = minPath == 1e7 ? 1e7 : minPath + matrix[i][j];
        };

        int result = INT_MAX;
        for (int j = 0; j <= m; j++) {
            result = std::min(recursive(0, j), result);
        }

        return result;
    }
};