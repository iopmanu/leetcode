class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::deque<int> q;
        std::vector<int> result(temperatures.size(), 0);

        for (int i = 0; i < temperatures.size(); ++i) {
            while (!q.empty() && temperatures[q.back()] < temperatures[i]) {
                result[q.back()] = (i - q.back());
                q.pop_back();
            }

            q.push_back(i);
        }

        return result;
    }
};