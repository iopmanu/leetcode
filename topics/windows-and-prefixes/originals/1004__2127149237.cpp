class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int zeroes = 0;
        int left = 0;

        int result = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                ++zeroes;
            }

            while (left < right && zeroes > k) {
                zeroes -= (nums[left++] == 0);
            }

            if (zeroes <= k) {
                result = std::max(right - left + 1, result);
            }
        }

        return result;
    }
};