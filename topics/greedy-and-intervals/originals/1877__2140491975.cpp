class Solution {
public:
    int minPairSum(vector<int>& nums) {
        std::unordered_map<int, int> freqs{};
        int min = INT_MAX; int max = INT_MIN;
        for (int i = 0; i < nums.size(); ++i) {
            min = std::min(min, nums[i]);
            max = std::max(max, nums[i]);
            ++freqs[nums[i]];
        }

        int result = 0;
        while (min <= max) {
            if (!freqs[min]) {
                ++min;
            } else if (!freqs[max]) {
                --max;
            } else {
                result = std::max(result, min + max);
                --freqs[min]; --freqs[max];
            }
        }

        return result;
    }
};