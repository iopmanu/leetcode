    bool canPartition(vector<int>& nums) {

        int total = std::accumulate(nums.begin(), nums.end(), 0);

        int memo[201][20001];
        std::memset(memo, -1, sizeof(memo));

        std::function<bool(int, int)> recursive = [&](int i, int sum) -> int {
            if (i == nums.size()) {
                return sum == (total - sum);
            }

            if (memo[i][sum] != -1) {
                return memo[i][sum];
            }

            return memo[i][sum] = (recursive(i + 1, sum + nums[i]) || recursive(i + 1, sum));
        };

        return recursive(0, 0) == 1;
    }
