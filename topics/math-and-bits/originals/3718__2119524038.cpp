class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        std::unordered_set<int> s{nums.begin(), nums.end()};

        int iter = 0;
        do {
            iter += k;
        } while (s.contains(iter));

        return iter;
    }
};