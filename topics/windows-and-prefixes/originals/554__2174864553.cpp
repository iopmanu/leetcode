class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        std::unordered_map<long long, long long> endEdges{};

        long long end = std::accumulate(wall[0].begin(), wall[0].end(), 0LL);
        for (int i = 0; i < wall.size(); ++i) {
            long long current = 0;
            for (auto&& brick : wall[i]) {
                current += brick;
                
                if (current != end) {
                    ++endEdges[current];
                }
            }
        }

        auto it = std::max_element(endEdges.begin(), endEdges.end(), [&](auto& l, auto& r) {
            return l.second < r.second;
        });

        return it == endEdges.end() ? wall.size() : wall.size() - it->second;
    }
};