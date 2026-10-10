class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        std::unordered_map<int, int> m;
        for (auto l : nums3) {
            for (auto r : nums4) {
                ++m[l + r];
            }
        }

        int count = 0;
        for (int l : nums1) {
            for (int r : nums2) {
                count += m[-(l + r)];
            }
        }

        return count;
    }
};