class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int left = 1; int right = 1e9;

        auto check = [&](int daysBudget) {
            int bouquets = 0; int currentStreak = 0;
            for (int i = 0; i < bloomDay.size(); i++) {
                if (bloomDay[i] <= daysBudget) {
                    ++currentStreak;
                } else {
                    currentStreak = 0;
                }

                if (currentStreak == k) {
                    currentStreak = 0;
                    ++bouquets;
                }
            }

            return bouquets >= m;
        };

        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left > 1e9 ? -1 : left;
    }
};