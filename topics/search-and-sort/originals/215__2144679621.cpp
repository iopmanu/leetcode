class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickselect(nums, 0, nums.size() - 1, nums.size() - k);
    }

    int quickselect(vector<int>& nums, int left, int right, int k) {
        if (left == right) {
            return nums[k];
        }

        int i = left; int j = right;
        int pivot = nums[left + (right - left) / 2];

        while (i <= j) {
            while (nums[i] < pivot) {
                i++;
            }

            while (nums[j] > pivot) {
                j--;
            }

            if (i <= j) {
                std::swap(nums[i++], nums[j--]);
            }
        }

        if (k <= j) {
            quickselect(nums, left, j, k);
        }

        else if (k >= i) {
            quickselect(nums, i, right, k);
        }

        return nums[k];
    }
};