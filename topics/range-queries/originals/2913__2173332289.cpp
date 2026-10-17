class Solution {
   
public:
    int sumCounts(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            std::unordered_set<int> seen{};
            for (int j = i; j < nums.size(); j++) {
                seen.insert(nums[j]);
                result += seen.size() * seen.size();
            }
        }

        return result;
    }
};