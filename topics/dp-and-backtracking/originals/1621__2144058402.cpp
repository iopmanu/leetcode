class Solution {
    long long mod = 1e9 + 7;
    long long dp[1005][1005][2];
public:
    int numberOfSets(int n, int k) {
        std::function<int(int, bool, int)> solve = [&](int idx, bool start, int k) -> int {
            if (k == 0) {
                return 1;
            }

            if (idx == n) {
                return 0;
            }

            if (dp[idx][k][start] != -1) {
                return dp[idx][k][start];
            }

            long long ans = 0;
            if (start) {
                ans = (ans + solve(idx, false, k - 1)) % mod;
                ans = (ans + solve(idx + 1, true, k)) % mod;
            } else {
                ans = (ans + solve(idx + 1, true, k)) % mod;
                ans = (ans + solve(idx + 1, false, k)) % mod;
            }

            return dp[idx][k][start] = ans;
        };

        memset(dp, -1, sizeof(dp));
        return solve(0, false, k);
    }
};