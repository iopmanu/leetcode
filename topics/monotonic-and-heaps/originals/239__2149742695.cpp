class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::priority_queue<std::pair<int, int>> pq{};

        std::vector<int> result{};
        for (int i = 0; i < k; ++i) {
            pq.push(std::make_pair(nums[i], i));
        }
        result.push_back(pq.top().first);
        
        for (int i = k; i < nums.size(); ++i) {
            pq.push(std::make_pair(nums[i], i));

            while (!pq.empty() && pq.top().second <= i - k) {
                pq.pop();
            }

            result.push_back(pq.top().first);
        }

        return result;
    }
};