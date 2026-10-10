class Solution {
public:
    // 1, 2, 5, 8, 13, 21

    int maximumTastiness(vector<int>& price, int k) {
        std::sort(price.begin(), price.end());

        int low = 0, high = price[price.size() - 1] - price[0];
        int result = 0;

        auto canPick = [&](int d) {
            int count = 1;
            int last = price[0];
            for (int i = 0; i < price.size(); i++) {
                if (price[i] - last >= d) {
                    ++count;
                    last = price[i];
                }

                if (count >= k) {
                    return true;
                }
            }

            return false;
        };

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canPick(mid)) {
                result = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return result;
    }
};