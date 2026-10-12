class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        std::deque<int> stk{};

        std::vector<int> result(nums.size(), -1);
        for (int i = 0; i < nums.size(); ++i) {
            while (!stk.empty() && nums[stk.back()] < nums[i]) {
                result[stk.back()] = nums[i];
                stk.pop_back();
            }

            stk.push_back(i);
        }

        for (int i = 0; i < nums.size(); ++i) {
            if (stk.empty() || i == stk.back()) {
                break;
            }

            while (!stk.empty() && nums[stk.back()] < nums[i]) {
                result[stk.back()] = nums[i];
                stk.pop_back();
            }
        }

        return result;
    }
};