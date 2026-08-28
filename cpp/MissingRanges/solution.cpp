#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> findMissingRanges(
            const std::vector<int>& nums,
            int lower,
            int upper
    ) {
        if (nums.empty()) {
            return {{lower, upper}};
        }

        std::vector<std::vector<int>> result;

        if (lower < nums.front()) {
            result.push_back({lower, nums.front() - 1});
        }

        for (int i = 0;
             i + 1 < static_cast<int>(nums.size());
             ++i) {
            if (static_cast<long long>(nums[i + 1]) - nums[i] > 1) {
                result.push_back({
                    nums[i] + 1,
                    nums[i + 1] - 1
                });
            }
        }

        if (nums.back() < upper) {
            result.push_back({nums.back() + 1, upper});
        }

        return result;
    }
};
