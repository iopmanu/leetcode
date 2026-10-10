class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        std::sort(
            intervals.begin(), intervals.end(),
            [&](const auto& l, const auto& r) {
                return l[1] < r[1];
            }
        );

        int result = 0;
        auto& last = intervals[0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= last[1]) {
                last = intervals[i];
            } else {
                ++result;
            }
        }

        return result;
    }
};