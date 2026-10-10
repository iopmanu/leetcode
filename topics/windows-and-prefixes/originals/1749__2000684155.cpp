class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int maxPrefix = 0, minPrefix = 0;
        int current = 0;
        for (auto&& num : nums) {
            current += num;
            maxPrefix = max(maxPrefix, current);
            minPrefix = min(minPrefix, current);
        }

        return maxPrefix - minPrefix;
    }
};