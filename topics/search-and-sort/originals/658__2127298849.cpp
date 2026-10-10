class Solution {
    using TQueue = std::priority_queue<std::vector<int>>;

public:
    vector<int> findClosestElements(vector<int>& nums, int k, int x) {
        int left = 0, right = nums.size() - 1;
        while (right - left >= k) {
            if (std::abs(nums[right] - x) >= std::abs(nums[left] - x)) {
                --right;
            } else {
                ++left;
            }
        }

        std::vector<int> result{};
        for (int i = left; i <= right; ++i) {
            result.push_back(nums[i]);
        }

        return result;
    }
};