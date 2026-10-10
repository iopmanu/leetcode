class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = *std::max_element(weights.begin(), weights.end());
        int right = std::accumulate(weights.begin(), weights.end(), 0);

        auto canShip = [&, days](int guess) {
            int d = 1;
            int load = 0;
            for (auto weight : weights) {
                if (load + weight > guess) {
                    load = 0;
                    ++d;
                }

                load += weight;
            }

            return d <= days;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canShip(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};