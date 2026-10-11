class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());

        int result = INT_MAX - 100000;
        for (int i = 0; i < nums.size() - 2; i++) {
            int left = i + 1; int right = nums.size() - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (std::abs(result  - target) > std::abs(sum - target)) {
                    result = sum;
                }

                if (sum > target) {
                    --right;
                } else {
                    ++left;
                }
            }
        }

        return result;
    }
};