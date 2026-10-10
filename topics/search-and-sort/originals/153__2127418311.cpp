class Solution {

    // [3,4,5,1,2]
    // l3, r2, m5
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums.back()) {
                left = mid + 1;
            } else {
                right = mid;
            }

        }

        return nums[left];
    }
};