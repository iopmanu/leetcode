class Solution {
public:
    vector<int> maxProductPair(vector<int>& nums, int target) {
        std::unordered_map<int, int> prevSum{};
        
        std::vector<std::vector<int>> pairs{};
        for (int i = 0; i < nums.size(); i++) {            
            if (prevSum.contains(target - nums[i])) {
                int j = prevSum[target - nums[i]];

                if (nums[i] > nums[j]) {
                    pairs.push_back({i, j});
                } else if (nums[j] > nums[i]) {
                    pairs.push_back({j, i});
                }
            }
            
            prevSum[nums[i]] = i;
        }

        if (pairs.empty()) {
            return {-1, -1};
        }

        auto it = std::max_element(pairs.begin(), pairs.end(), [&](auto& l, auto& r) {
            return nums[l[0]] * nums[l[1]] < nums[r[0]] * nums[r[1]];
        });

        return *it;
    }
};