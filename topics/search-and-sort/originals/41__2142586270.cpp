class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        long long max = *std::max_element(nums.begin(), nums.end());
        long long min = *std::min_element(nums.begin(), nums.end());
        
        std::unordered_map<long long, bool> isPresent{};
        for (auto num : nums) {
            isPresent[num] = true;
        }

        for (long long i = 1; i < max; ++i) {
            if (!isPresent.contains(i)) {
                return i;
            }
        }

        return max < 0 ? 1 : max + 1;
    }
};