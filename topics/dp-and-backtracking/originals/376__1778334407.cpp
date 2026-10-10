class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        size_t up = 1, down = 1;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            if (nums[i] > nums[i + 1]) {
                up = down + 1;
            } else if (nums[i] < nums[i + 1]) {
                down = up + 1;
            }
        }

        return std::max(up, down);
    }
};