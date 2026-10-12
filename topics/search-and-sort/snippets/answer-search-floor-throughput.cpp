class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        long long left = 1; long long right = 1LL * totalTrips * *std::min_element(time.begin(), time.end());

        auto check = [&](long long minTime) {
            long long trips = 0;
            for (auto bus : time) {
                trips += minTime / bus;
            }

            return trips >= totalTrips;
        };
    
        while (left <= right) {
            long long mid = left + ((right - left) >> 1);
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};