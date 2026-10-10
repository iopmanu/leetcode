class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        std::vector<std::pair<int, int>> speedWithPos{};
        for (int i = 0; i < position.size(); ++i) {
            speedWithPos.push_back(std::make_pair(
                position[i], speed[i]
            ));
        }

        std::sort(speedWithPos.begin(), speedWithPos.end());

        int result = 0;
        std::stack<double> steps{};
        for (int i = 0; i < speedWithPos.size(); ++i) {
            double time = (target - speedWithPos[i].first) / (double) speedWithPos[i].second;
            while (!steps.empty() && steps.top() <= time) {
                steps.pop();
            }

            steps.push(time);
        }

        return steps.size();
    }
};