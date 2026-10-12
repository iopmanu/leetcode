class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        for (int i = 0; i < intervals.size(); i++) {
            intervals[i].push_back(i);
        }
        std::sort(intervals.begin(), intervals.end());
        std::vector<int> result(intervals.size(), -1);

        for (auto&& interval : intervals) {
            int left = 0; int right = intervals.size();
            while (left < right) {
                int mid = left + ((right - left) >> 1);
                if (intervals[mid][0] < interval[1]) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            result[interval[2]] = (left == intervals.size() ? -1 : intervals[left][2]);
        }

        return result;
    }
};