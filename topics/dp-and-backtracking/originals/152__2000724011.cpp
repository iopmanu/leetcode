class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int retval = nums[0];
        int currMax = nums[0];
        int currMin = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            int prevMax = currMax;
            int prevMin = currMin;

            currMax = max({nums[i], prevMax * nums[i], prevMin * nums[i]});
            currMin = min({nums[i], prevMax * nums[i], prevMin * nums[i]});

            retval = max(currMax, retval);
        }
        
        return retval;
    }
};