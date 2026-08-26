#include <algorithm>
#include <vector>

class Solution {
public:
    int findMaxConsecutiveOnes(const std::vector<int>& nums) {
        int result = 0;
        int zeros = 0;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            zeros += (nums[right] == 0);

            while (zeros > 1) {
                zeros -= (nums[left] == 0);
                ++left;
            }

            result = std::max(result, right - left + 1);
        }

        return result;
    }
};
