class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) {
            return 0;
        }

        if (nums[0] > nums[1]) {
            return 0;
        }

        if (*(nums.end() - 1) > *(nums.end() - 2)) {
            return nums.size() - 1;
        }

        int low = 1, high = nums.size() - 2;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[mid + 1] && nums[mid] > nums[mid - 1]) {
                return mid;
            } else if (nums[mid - 1] > nums[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return -1;
    }
};