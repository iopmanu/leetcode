class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end(), [&](int l, int r) {
            return std::abs(l) < std::abs(r);
        });
        long long sum = 0; int left = 0; int right = nums.size() - 1;

        bool isRightChoise = true;
        while (left <= right) {
            if (isRightChoise) {
                sum += 1LL * nums[right] * nums[right];
                --right;
                isRightChoise = false;
            } else {
                sum -= 1LL * nums[left] * nums[left];
                ++left;
                isRightChoise = true;
            }
        }

        return sum;
    }
};