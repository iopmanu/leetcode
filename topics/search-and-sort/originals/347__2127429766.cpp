class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> counts{};
        for (int i = 0; i < nums.size(); ++i) {
            ++counts[nums[i]];
        }

        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::less<std::vector<int>>> pq{};
        for (const auto [v, c] : counts) {
            pq.push({c, v});
        }

        std::vector<int> result{};
        for (int i = 0; i < k; ++i) {
            result.push_back(pq.top()[1]);
            pq.pop();
        }

        return result;
    }
};