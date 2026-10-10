// prefix[right] - prefix[left] = k
// prefix[left] = prefix[right] - k

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        std::unordered_map<int, int> counts{};
        counts[0] = 1;
        int current = 0;

        int result = 0;
        for (auto num : nums) {
            current += num;
            if (auto found = counts.find(current - k); found != counts.end()) {
                result += found->second;
            }

            ++counts[current];
        }

        return result;
    }
};