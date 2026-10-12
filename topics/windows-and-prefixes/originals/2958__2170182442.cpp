class Solution {
public:
    int maxSubarrayLength(vector<int>& nums, int k) {
        int left = 0;
        int result = 0;
        std::unordered_map<int, int> freq{};
        for (int right = 0; right < nums.size(); right++) {
            freq[nums[right]]++;
            while (left < right && freq[nums[right]] > k) {
                freq[nums[left++]]--;
            }

            result = std::max(result, right - left + 1);
        }

        return result;
    }
};