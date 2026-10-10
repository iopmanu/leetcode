class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            int current = 0;
            while (nums[i] > 0) {
                current += nums[i] % 10;
                nums[i] /= 10;
            }

            if (current == i) {
                return i;
            }
        }

        return -1;
    }
};