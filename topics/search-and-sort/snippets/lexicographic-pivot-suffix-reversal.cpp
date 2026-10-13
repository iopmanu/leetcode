class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int left = nums.size() - 1;
        for (; left > 0; --left) {
            if (nums[left - 1] < nums[left]) {
                break;
            }
        }

        if (left == 0) {
            std::reverse(nums.begin(), nums.end());
            return;
        }

        for (int right = nums.size() - 1; right >= left; --right) {
            if (nums[right] > nums[left - 1]) {
                std::swap(nums[left - 1], nums[right]);
                std::reverse(nums.begin() + left, nums.end());
                return;
            }
        }
    }
};