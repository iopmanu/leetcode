class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long left = -1;

        long maximumIndex = -1;
        long minimumIndex = -1;

        long result = 0;
        for (long right = 0; right < nums.size(); ++right) {
            if (nums[right] < minK || nums[right] > maxK) {
                left = right;
            }

            if (nums[right] == minK) {
                minimumIndex = right;
            }

            if (nums[right] == maxK) {
                maximumIndex = right;
            }

            result += std::max(0L, std::min(maximumIndex, minimumIndex) - left);
        }

        return result;
    }
};