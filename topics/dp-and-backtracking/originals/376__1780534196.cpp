class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        std::vector<int> up(nums.size(), 1);
        std::vector<int> down(nums.size(), 1);

        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] > nums[i - 1]) {
                up[i] = down[i - 1] + 1;
                down[i] = down[i - 1];
            } else if (nums[i] < nums [i - 1]) {
                up[i] = up[i - 1];
                down[i] = up[i - 1] + 1;
            } else {
                up[i] = up[i - 1];
                down[i] = down[i - 1];
            }
        }

        return std::max(down.back(), up.back());
    }
};