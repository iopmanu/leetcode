class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        std::unordered_map<char, int> counts{};
        for (char task : tasks) {
            ++counts[task];
        }

        std::priority_queue<int> pq{};
        for (auto& entry : counts) {
            pq.push(entry.second);
        }

        int result = 0;
        while (!pq.empty()) {
            std::vector<int> remain;

            for (int i = 0; i <= n && !pq.empty(); i++) {
                remain.push_back(pq.top());
                pq.pop();
            }

            for (int freq : remain) {
                if (freq > 1) {
                    pq.push(freq - 1);
                }
            }

            result += pq.empty() ? remain.size() : n + 1;
        }

        return result;
    }
};