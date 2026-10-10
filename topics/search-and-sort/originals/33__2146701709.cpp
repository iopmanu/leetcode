class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0; int right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums.back()) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        int pivot = left;
        left = 0; right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left / 2);
            int toCheck = (mid + pivot) % nums.size();

            if (nums[toCheck] == target) {
                return toCheck;
            } else if (nums[toCheck] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};