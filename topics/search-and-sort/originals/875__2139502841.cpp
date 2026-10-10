class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1; int right = *std::max_element(piles.begin(), piles.end());

        auto canEat = [&, h](auto k) {
            int hours = 0;
            for (auto bananas : piles) {
                hours += (bananas / k) + (bananas % k != 0);
            }

            return hours <=h;
        };

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canEat(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};