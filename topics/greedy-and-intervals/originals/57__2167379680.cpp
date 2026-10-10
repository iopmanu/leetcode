class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        std::sort(intervals.begin(), intervals.end());

        auto left = std::lower_bound(
            intervals.begin(), intervals.end(), newInterval[0],
            [&](auto& interval, int target) {
                return interval[1] < target;
            }
        );

        auto right = std::upper_bound(
            intervals.begin(), intervals.end(), newInterval[1],
            [&](int target, auto& interval) {
                return target < interval[0];
            }
        );

        if (left != right) {
            newInterval[0] = std::min(newInterval[0], (*left)[0]);
            newInterval[1] = std::max(newInterval[1], (*std::prev(right))[1]);
        }

        auto erase = intervals.erase(left, right);
        intervals.insert(erase, newInterval);

        return intervals;
    }
};