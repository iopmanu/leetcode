class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        std::vector<int> min(nums.size(), INT_MAX);
        min[nums.size() - 1] = nums.back();
        for (int i = nums.size() - 2; i >= 0; --i) {
            min[i] = std::min(nums[i], min[i + 1]);
        }

        int max = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            max = std::max(max, nums[i]);
            if (max - min[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};