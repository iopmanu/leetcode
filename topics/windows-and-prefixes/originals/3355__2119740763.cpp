class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        std::vector<int> diffs(nums.size() + 1, 0);
        for (const auto& q : queries) {
            ++diffs[q[0]];
            --diffs[q[1] + 1];
        }

        int capacity = 0;
        for (int i = 0; i < nums.size(); ++i) {
            capacity += diffs[i];
            if (capacity < nums[i]) {
                return false;
            }
        }

        return true;
    }
};