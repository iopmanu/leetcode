class Solution {
public:
    int peakIndexInMountainArray(vector<int>& nums) {
        int left = 0; int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int leftBound = mid > 0 ? nums[mid - 1] : INT_MIN;
            int rightBound = mid < nums.size() - 1 ? nums[mid + 1] : INT_MIN;

            if (leftBound < nums[mid] && rightBound < nums[mid]) {
                return mid;
            } else if (leftBound < nums[mid] && rightBound > nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return left;
    }
};