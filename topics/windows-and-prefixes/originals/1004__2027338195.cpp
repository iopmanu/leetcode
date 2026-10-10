class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, result = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                --k;
            }

            if (k < 0) {
                if (nums[left] == 0) {
                    ++k;
                }

                ++left;
            }

            result = std::max(right - left + 1, result);
        }

        return result;
    }
};