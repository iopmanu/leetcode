class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = INT_MIN, current = 0;
        for (int num : nums) {
            current += num;
            sum = max(sum, current);

            if (current < 0) {
                current = 0;
            }
        }

        return sum;
    }
};