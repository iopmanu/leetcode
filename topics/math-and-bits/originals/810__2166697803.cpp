class Solution {
    // [1,1, 1, 1, 2, 3]
    // []
public:
    bool xorGame(vector<int>& nums) {
        int x = 0;
        for (int i : nums) {
            x ^= i;
        }
        return x == 0 || nums.size() % 2 == 0;
    }
};