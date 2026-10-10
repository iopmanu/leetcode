    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(),[&](auto& l, auto& r) {
            return l[1] < r[1];
        });

        auto& last = intervals[0];
        int result = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (last[1] <= intervals[i][0]) {
                last = intervals[i];
            } else {
                ++result;
            }
        }

        return result;
    }
