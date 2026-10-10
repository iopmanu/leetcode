class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());

        auto check = [&](int guess) -> bool {
            int current = 0;
            for (int i = 0; i < piles.size(); i++) {
                current += (piles[i] / guess) + (piles[i] % guess != 0);
                if (current > h) {
                    return false;
                }
            }

            return true;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (check(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};