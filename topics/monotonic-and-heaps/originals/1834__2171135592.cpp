class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        for (int i = 0; i < tasks.size(); i++) {
            tasks[i].push_back(i);
        }

        std::sort(tasks.begin(), tasks.end());
        int ptr = 0; long long time = tasks[ptr][0];
        
        std::vector<int> order{};
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<>> pq{};
        while (ptr < tasks.size() || !pq.empty()) {
            if (pq.empty() && time < tasks[ptr][0]) {
                time = tasks[ptr][0];
            }

            while (ptr < tasks.size() && tasks[ptr][0] <= time) {
                pq.push({tasks[ptr][1], tasks[ptr][2]});
                ++ptr;
            }

            while (!pq.empty() && (ptr == tasks.size() || time < tasks[ptr][0])) {
                order.push_back(pq.top()[1]);
                time += pq.top()[0];
                pq.pop();
            }
        }

        return order;
    }
};