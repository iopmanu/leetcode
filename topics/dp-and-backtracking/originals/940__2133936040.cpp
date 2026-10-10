class Solution {
    std::array<int, 26> lastseen{-1};
    std::vector<int> dp{};
    std::vector<int> prev{};
    long long MOD = std::pow(10, 9) + 7;

public:
    int distinctSubseqII(string s) {
        lastseen.fill(-1);
        dp = std::vector<int>(s.size() + 1, -1);
        prev = std::vector<int>(s.size() + 1, -1);

        dp[0] = 1;
        
        long long result = 0;
        for (int i = 1; i <= s.size(); ++i) {
            int idx = s[i - 1] - 'a';
            prev[i] = lastseen[idx];
            lastseen[idx] = i;
        }
        
        return (solve(s.size()) + MOD - 1) % MOD;
    }

    int solve(int i) {
        if (i == 0) {
            return 1;
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        int total = (2 * solve(i - 1)) % MOD;
        if (prev[i] != -1) {
            int duplicates = solve(prev[i] - 1);
            total = (total - duplicates + MOD) % MOD;
        }

        return dp[i] = (int) total % MOD;
    }
};