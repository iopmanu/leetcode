class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        std::priority_queue<int, std::vector<int>, std::less<int>> pq{};
        for (auto stone : stones) {
            pq.push(stone);
        }

        while (pq.size() > 1) {
            auto l = pq.top();
            pq.pop();
            auto r = pq.top();
            pq.pop();

            auto diff = std::abs(l - r);
            if (diff) {
                pq.push(diff);
            }
        }

        return pq.empty() ? 0 : pq.top();
    }
};