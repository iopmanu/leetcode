class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::less<int>> pq{};
        for (int i = 0; i < nums.size(); ++i) {
            pq.push(nums[i]);
        }

        for (int i = 0; i < k - 1; ++i) {
            pq.pop();
        }

        return pq.top();
    }
};