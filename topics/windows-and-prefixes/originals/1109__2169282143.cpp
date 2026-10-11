class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        std::vector<int> timeline(n + 1, 0);
        for (auto&& b : bookings) {
            timeline[b[0] - 1] += b[2];
            timeline[b[1]] -= b[2];
        }

        std::vector<int> result(n, 0);
        int current = 0;
        for (int i = 0; i < n; i++) {
            current += timeline[i];
            result[i] = current;
        }

        return result;
    }
};