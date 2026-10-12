class Solution {
public:
    int resilientSubarray(vector<int>& nums, int k) {
        int result = 1;
        int left = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] % k != nums[left] % k) {
                left = right;
            }

            int length = right - left + 1;
            int remainder = ((nums[right] % k) + k) % k;

            while (length > result) {
                if ((1LL * (length - 1) * remainder) % k == 0) {
                    result = length;
                    break;
                }
                --length;
            }
        }

        return result;
    }
};
