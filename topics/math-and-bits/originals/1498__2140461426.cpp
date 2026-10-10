class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        static int MOD = std::pow(10, 9) + 7;
        
        std::sort(nums.begin(), nums.end());

        std::vector<int> power(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i) {
            power[i] = (power[i - 1] * 2) % MOD;
        }

        int result = 0;
        int left = 0; int right = nums.size() - 1;
        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                result = (result + power[right - left]) % MOD;
                ++left;
            } else {
                --right;
            }
        }

        return result;
    }
};