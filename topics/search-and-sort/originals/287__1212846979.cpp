class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        std::unordered_set<int> occurences;
        for (auto && elem: nums) {
            if (occurences.find(elem) != occurences.end()) {
                return elem;
            }

            occurences.insert(elem);
        }
        
        return -1;
    }
};