class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<>> pq{};
        for (int i = 0; i < k && i < nums1.size(); i++) {
            pq.push({nums1[i] + nums2[0], i, 0});
        }

        std::vector<std::vector<int>> result{};
        while (!pq.empty() && k > 0) {
            int sum = pq.top()[0]; int i = pq.top()[1]; int j = pq.top()[2];
            pq.pop();

            result.push_back({nums1[i], nums2[j]});
            --k;

            if (j + 1 < nums2.size()) {
                pq.push({nums1[i] + nums2[j + 1], i, j + 1});
            }
        }

        return result;
    }
};