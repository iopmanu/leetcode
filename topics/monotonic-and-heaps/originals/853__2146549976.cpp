class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        std::vector<std::pair<int, double>> speedWithPos{};
        for (int i = 0; i < position.size(); ++i) {
            speedWithPos.push_back(std::make_pair(
                position[i], (target - position[i]) / (double) speed[i]
            ));
        }

        std::sort(speedWithPos.begin(), speedWithPos.end());

        std::stack<double> steps{};
        for (int i = 0; i < speedWithPos.size(); ++i) {
            while (!steps.empty() && steps.top() <= speedWithPos[i].second) {
                steps.pop();
            }

            steps.push(speedWithPos[i].second);
        }

        return steps.size();
    }
};