class Solution {
    std::unordered_map<int, int> cache{};
public:
    int rob(vector<int>& nums) {
        std::vector<int> dp{};
        dp.reserve(nums.size());

        if (nums.size() <= 1) {
            return nums[0];
        }

        dp.push_back(nums[0]);
        dp.push_back(max(nums[0], nums[1]));

        for (int i = 2; i < nums.size(); i++) {
            dp.push_back(max(dp[i - 1], nums[i] + dp[i - 2]));
        }

        return dp.back();
    }
};