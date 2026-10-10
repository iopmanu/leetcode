class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0;

        int zeroes = 0;
        int result = 0;
        for (int right = 0; right < nums.size(); ++right) {
            zeroes += (nums[right] == 0);

            if (zeroes > 1) {
                zeroes -= (nums[left++] == 0);
            } else {
                result = std::max(result, right - left);
            }
        }

        return result;
    }
};