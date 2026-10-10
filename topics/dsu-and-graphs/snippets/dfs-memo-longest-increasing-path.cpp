class Solution {
    std::vector<std::vector<int>> dp{};
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        dp.resize(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            dp[i].resize(matrix[0].size(), -1);
        }

        int result = 0;
        std::unordered_set<long long> visited;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                result = std::max(result, dfs(i, j, -1, matrix, visited));
            }
        }

        return result;
    }

    int dfs(
        int i, int j, int prev,
        std::vector<std::vector<int>>& matrix,
        std::unordered_set<long long>& visited
    ) {
        if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size()) {
            return 0;
        }

        long long key = ((long long) i << 32) | (long long) j;
        if (visited.contains(key)) {
            return 0;
        }

        if (matrix[i][j] <= prev) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        visited.insert(key);

        dp[i][j] = 1 + std::max({
            dfs(i - 1, j, matrix[i][j], matrix, visited),
            dfs(i + 1, j, matrix[i][j], matrix, visited),
            dfs(i, j - 1, matrix[i][j], matrix, visited),
            dfs(i, j + 1, matrix[i][j], matrix, visited)
        });

        visited.erase(key);

        return dp[i][j];
    }
};