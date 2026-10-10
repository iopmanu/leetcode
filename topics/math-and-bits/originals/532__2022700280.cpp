class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> counts;
        for (int n : nums) ++counts[n];

        set<pair<int,int>> result;
        for (auto [num, cnt] : counts) {
            if (k == 0) {
                if (cnt > 1) result.insert({num, num});
            } else {
                if (counts.count(num + k))
                    result.insert({num, num + k});
            }
        }
        return result.size();
    }
};