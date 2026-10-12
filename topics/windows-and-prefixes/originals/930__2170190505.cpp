class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        int count = 0; int current = 0;
        std::unordered_map<int, int> prefixSumCount{};
        prefixSumCount[0] = 1;

        for (int right = 0; right < nums.size(); ++right) {
            current += nums[right];
            count += prefixSumCount[current - goal];
            prefixSumCount[current]++;
        }

        return count;
    }
};