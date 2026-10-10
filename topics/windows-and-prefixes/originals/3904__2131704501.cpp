class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        std::vector<int> minimums(nums.size(), INT_MAX);
        int current = INT_MAX;
        for (int i = nums.size() -1 ; i >= 0; --i) {
            current = std::min(current, nums[i]);
            minimums[i] = current;
        }

        current = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            current = std::max(current, nums[i]);
            if (current - minimums[i] <= k) {
                return i;
            }
        }

        return -1;
    }
};