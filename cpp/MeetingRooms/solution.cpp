#include <algorithm>
#include <vector>

class Solution {
public:
    bool canAttendMeetings(
            std::vector<std::vector<int>>& intervals
    ) {
        std::sort(
            intervals.begin(),
            intervals.end(),
            [](const auto& l, const auto& r) {
                return l[0] < r[0] ||
                       (l[0] == r[0] && l[1] < r[1]);
            }
        );

        for (int i = 0;
             i < static_cast<int>(intervals.size()) - 1;
             ++i) {
            if (intervals[i][1] > intervals[i + 1][0]) {
                return false;
            }
        }

        return true;
    }
};
