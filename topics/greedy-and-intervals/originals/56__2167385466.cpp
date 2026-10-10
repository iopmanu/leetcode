class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end());

        std::vector<std::vector<int>> result{};
        for (auto&& interval : intervals) {
            if (!result.empty() && result.back()[1] >= interval[0]) {
                result.back()[1] = std::max(result.back()[1], interval[1]);
            } else {
                result.push_back(interval);
            }
        }

        return result;
    }
};