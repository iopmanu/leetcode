class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> result(k);
        std::vector<long long> dp(k);

        for (int i = 0; i < n; ++i) {
            std::vector<long long> ndp(k);
            ndp[nums[i] % k]++;
            
            for (int r = 0; r < k; r++) {
                ndp[(long long)r * nums[i] % k] += dp[r];
            }

            dp = std::move(ndp);

            for (int r = 0; r < k; r++) {
                result[r] += dp[r];
            }
        }

        return result;
    }
};