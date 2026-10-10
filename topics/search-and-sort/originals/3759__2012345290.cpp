class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        if (k == 0) {
            return nums.size();
        }
        std::sort(nums.begin(), nums.end());
        
        int result = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int upb = upperBound(nums, nums[i]);
            if (((nums.size() - upb + 1) > k) && nums[upb] > nums[i]) {
                ++result;
            }
        }

        return result;
    }

    int upperBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;
    }
};