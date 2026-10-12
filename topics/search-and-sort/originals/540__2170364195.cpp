class Solution {
    //      *
    // [1,1,2,3,3,4,4,8,8]
    //  0 1 2 3 4 5 6 7 8
    //
    //          *
    // [3,3,7,7,10,11,11]
    //  0 1 2 3 4 5 6 7

    // if 
public:
    int singleNonDuplicate(vector<int>& nums) {
        int left = 0; int right = nums.size() - 1;
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            
            if (nums[mid] == nums[mid ^ 1]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return nums[left];
    }
};