class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        std::unordered_set<int> occur;
        for (auto num : nums) {
            if (occur.contains(num)) {
                return num;
            }

            occur.insert(num);
        }

        return -1;
    }
};