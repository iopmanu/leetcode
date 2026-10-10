class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        int left = 0, right = *std::max_element(nums.begin(), nums.end());

        auto canRob = [&](int guess) {
            int robbed = 0;
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] <= guess) {
                    i++;
                    robbed++;
                }
            }

            return robbed >= k;
        };

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canRob(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};