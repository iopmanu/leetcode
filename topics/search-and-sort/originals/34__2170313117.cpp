class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) {
            return {-1, -1};
        }

        if (nums.size() == 1) {
            int idx = nums[0] == target ? 0 : -1;
            return {idx, idx};
        }
        
        int left = 0; int right = nums.size() - 1;
        std::vector<int> result{};

        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        left = nums[left] == target ? left : -1;
        result.push_back(left);

        left = 0; right = nums.size();
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        left = left > 0 && nums[left - 1] == target ? left - 1 : -1;
        result.push_back(left);

        return result;
    }
};
