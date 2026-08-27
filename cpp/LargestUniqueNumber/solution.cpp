#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
public:
    int largestUniqueNumber(const std::vector<int>& nums) {
        std::unordered_map<int, int> counts{};

        for (int num : nums) {
            ++counts[num];
        }

        int result = -1;

        for (const auto [number, count] : counts) {
            if (count == 1) {
                result = std::max(number, result);
            }
        }

        return result;
    }
};
