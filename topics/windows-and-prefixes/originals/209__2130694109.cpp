class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;

        int result = INT_MAX;
        int current = 0;
        for (int right = 0; right < nums.size(); ++right) {
            current += nums[right];
            while (current >= target) {
                result = std::min(result, right - left + 1);
                current -= nums[left++];
            }
        }

        return result == INT_MAX ? 0 : result;
    }
};