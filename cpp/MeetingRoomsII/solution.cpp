#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

class Solution {
public:
    int minMeetingRooms(
            std::vector<std::vector<int>>& intervals
    ) {
        std::sort(intervals.begin(), intervals.end());

        int minCount = 0;
        std::priority_queue<int, std::vector<int>, std::greater<int>> ends{};
        for (auto i = 0; i < intervals.size(); ++i) {
            while (!ends.empty() && ends.top() <= intervals[i][0]) {
                ends.pop();
            }

            ends.push(intervals[i][1]);
            minCount = std::max(minCount, static_cast<int>(ends.size()));
        }

        return minCount;
    }
};
