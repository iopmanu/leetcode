class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
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

        int low = *std::max_element(weights.begin(), weights.end()); 
        int high = std::accumulate(weights.begin(), weights.end(), 0);
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canShip(mid)) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};