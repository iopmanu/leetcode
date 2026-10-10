class Solution {
public:

    // sum(i, j) = sum(0, j) - sum(0, i)
    // sum(0, i) = sum(0, j) - k
    int subarraySum(vector<int>& nums, int k) {
        std::unordered_map<int, int> prefixes{};
        prefixes[0] = 1;

        int result = 0;
        int prefix = 0;
        for (int i = 0; i < nums.size(); ++i) {
            prefix += nums[i];

            result += prefixes[prefix - k];
            ++prefixes[prefix];
        }

        return result;
    }
};