class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());

        int result = 0;
        for (auto num : s) {
            if (s.contains(num - 1)) continue;

            int current = 1;
            int y = num + 1;
            while (s.contains(y)) {
                ++y;
                ++current;
            }

            result = std::max(result, current);
        }

        return result;
    }
};