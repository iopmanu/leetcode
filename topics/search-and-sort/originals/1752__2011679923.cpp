class Solution {
public:
    bool check(vector<int>& nums) {
        int pivot = INT_MIN;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < nums[i - 1]) {
                pivot = i;
                break;
            }
        }

        if (pivot == INT_MIN) {
            return true;
        }

        for (int i = pivot + 1; i < nums.size(); ++i) {
            if (nums[i] < nums[i - 1]) {
                return false;
            }
        }

        if (nums[nums.size() - 1] > nums[0]) {
            return false;
        }

        return true;
    }
};