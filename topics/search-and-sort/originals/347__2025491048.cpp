class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> counter{};
        for (auto num : nums) {
            counter[num]++;
        }

        std::set<std::pair<int, int>> q;
        for (auto [key, v] : counter) {
            q.insert({v, key});

            while (q.size() > k) {
                q.erase(q.begin());
            }
        }

        std::vector<int> result{};
        result.reserve(k);
        for (auto it = q.begin(), end = q.end(); it != end; ++it) {
            result.push_back(it->second);
        }

        return result;
    }
};