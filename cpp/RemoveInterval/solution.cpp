#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> removeInterval(
            const std::vector<std::vector<int>>& intervals,
            const std::vector<int>& toBeRemoved
    ) {
        std::vector<std::vector<int>> result{};
        result.reserve(intervals.size());

        for (const auto& interval : intervals) {
            if (interval[1] <= toBeRemoved[0] || interval[0] >= toBeRemoved[1]) {
                result.push_back(interval);
                continue;
            }

            if (interval[0] < toBeRemoved[0]) {
                result.push_back({interval[0], toBeRemoved[0]});
            }

            if (interval[1] > toBeRemoved[1]) {
                result.push_back({toBeRemoved[1], interval[1]});
            }
        }

        return result;
    }
};
