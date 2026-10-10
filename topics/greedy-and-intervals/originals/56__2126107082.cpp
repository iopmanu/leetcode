class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::vector<std::vector<int>> result{};
        std::sort(intervals.begin(), intervals.end());

        for (const auto& interval : intervals) {
            if (result.empty() || result.back()[1] < interval[0]) {
                result.emplace_back(interval);
                continue;
            }

            result.back()[1] = std::max(result.back()[1], interval[1]);
        }

        return result;
    }
};