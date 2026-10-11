    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int left = 0;
        int current = 1; int result = 0;
        for (int right = 0; right < nums.size(); ++right) {
            current *= nums[right];

            while (current >= k && left <= right) {
                current /= nums[left++];
            }

            if (current < k) {
                result += right - left + 1;
            }
        }

        return result;
    }
