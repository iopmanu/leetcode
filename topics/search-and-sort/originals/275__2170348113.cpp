class Solution {
public:
    int hIndex(vector<int>& citations) {
        auto getPapersCount = [&](int bound) {
            int count = 0;
            for (int i = 0; i < citations.size(); i++) {
                if (citations[i] >= bound) {
                    ++count;
                }
            }

            return count;
        };

        int l = 0; int r = citations.size();
        int result = 0;
        while (l <= r) {
            int mid = l + ((r - l) >> 1);
            if (getPapersCount(mid) >= mid) {
                result = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        return result;
    }
};