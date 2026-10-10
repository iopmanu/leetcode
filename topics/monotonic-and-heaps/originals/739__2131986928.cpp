class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        std::deque<int> s{};

        std::vector<int> result(temperatures.size(), 0);
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!s.empty() && temperatures[s.back()] < temperatures[i]) {
                result[s.back()] = i - s.back();
                s.pop_back();
            }

            s.push_back(i);
        }

        return result;
    }
};