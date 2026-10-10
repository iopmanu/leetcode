class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        // positive integers start with 1
        // we start scan from 1 and max number we can cover at here without skip is n + 1
        // because the total length of the nums is n. and if there is no skip at all our answer == n + 1
        // so all negative number and number > n are irrelevant
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= 0 || nums[i] > n) {
                nums[i] = n + 1;
            }
        }        

        // if the number wasn't converted to n + 1 -- it's relevant
        // for now our array contains only positive numbers
        // how to mark that from num - 1 there is an ancestor in the array?
        // correct -- make it negative
        // so if a number is negative -- it has an ancestor in array
        for (int i = 0; i < n; ++i) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }

        // if nums[i] hasn't ancestor nums[i] + 1 -> it will be a positive nubmer
        // and we will return the first occurence of this situtation
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }

        // otherwise return n + 1 because we cover all number [1, n]
        return n + 1;
    }
};