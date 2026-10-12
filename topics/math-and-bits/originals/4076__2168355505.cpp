class Solution {
public:
    int resilientSubarray(vector<int>& nums, int k) {
        int result = 1;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % k != nums[left] % k) {
                left = right;
            }

            int len = right - left + 1;
            int rem = nums[right] % k;

            int step = k / std::gcd(k, rem);
            int best = len - (len - 1) % step;

            result = std::max(result, best);
        }

        return result;
    }
};