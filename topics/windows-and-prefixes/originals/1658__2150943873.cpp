class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum < x) {
            return -1;
        }

        int toFind = sum - x;
        int left = 0; int current = 0;
        int retval = -1;
        for (int right = 0; right < nums.size(); ++right) {
            current += nums[right];
            while (current > toFind) {
                current -= nums[left++];
            }

            if (current == toFind) {
                retval = std::max(retval, right - left + 1);
            }
        }

        return retval == -1 ? -1 : nums.size() - retval;
    }
};