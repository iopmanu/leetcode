class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1, high = *std::max_element(piles.begin(), piles.end());

        auto canEat = [&](int guess) {
            int hours = 0;
            for (int i = 0; i < piles.size(); i++) {
                hours += (piles[i] / guess) + (piles[i] % guess != 0);
            }

            return hours <= h;
        };

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (canEat(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        return low;
    }
};