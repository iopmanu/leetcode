

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        std::vector<int> left(nums.size() + 1, 1);
        std::vector<int> right(nums.size() + 1, 1);
        for (int i = 0; i < nums.size(); ++i) {
            left[i + 1] = nums[i] * left[i];
        }

        for (int i = nums.size() - 1; i >= 0; --i) {
            right[i]  = nums[i] * right[i + 1];
        }

        std::vector<int> result{};
        for (int i = 0; i < nums.size(); ++i) {
            result.emplace_back(left[i] * right[i + 1]);
        }

        return result;
    }
};