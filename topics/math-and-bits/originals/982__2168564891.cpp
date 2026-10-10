class Solution {
public:
    int countTriplets(vector<int>& nums) {
        std::unordered_map<int, int> pairs{};
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums.size(); j++) {
                pairs[(nums[i] & nums[j])]++;
            }
        }

        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (auto&& [k, freq] : pairs) {
                if ((nums[i] & k) == 0) {
                    result += freq;
                }
            }
        }

        return result;
    }
};