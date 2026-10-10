class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        std::priority_queue<std::vector<int>> pq{};
        for (auto&& point : points) {
            pq.push({
                int(point[0] * point[0] + point[1] * point[1]),
                point[0], point[1]
            });
            
            if (pq.size() > k) {
                pq.pop();
            }
        }

        std::vector<std::vector<int>> result{};
        while (!pq.empty()) {
            result.push_back({pq.top()[1], pq.top()[2]});
            pq.pop();
        }

        return result;
    }
};