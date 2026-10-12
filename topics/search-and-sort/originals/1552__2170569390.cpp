class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        int left = 1; int right = *std::max_element(position.begin(), position.end());
        std::sort(position.begin(), position.end());

        auto check = [&](int guess) {
            int baskets = 1;
            int compare = position[0];
            for (int i = 1; i < position.size(); i++) {
                if (std::abs(compare - position[i]) >= guess) {
                    ++baskets;
                    compare = position[i];
                }
            }

            return baskets >= m;
        };

        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid)) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return right;
    }
};