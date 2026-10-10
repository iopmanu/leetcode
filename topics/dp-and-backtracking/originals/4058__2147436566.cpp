class Solution {
public:
    long long maxValue(vector<int>& nums) {
        int n = nums.size();
        long long base_sum = 0;
        for (int i = 0; i < n; ++i) {
            base_sum += (i % 2 == 0) * nums[i];
            base_sum -= (i % 2 == 1) * nums[i];
        }

        long long max = 0, current = 0;
        for (int i = 0; i + 1 < n; i += 2) {
            long long profit = 2LL * nums[i + 1] - 2LL * nums[i];
            current = std::max(0LL, current + profit);
            max = std::max(current, max);
        }

        current = 0;
        for (int i = 1; i + 1 < n; i += 2) {
            long long profit = 2LL * nums[i] - 2LL * nums[i + 1];
            current = std::max(0LL, current + profit);
            max = std::max(current, max);
        }

        return base_sum + max;
    }
};