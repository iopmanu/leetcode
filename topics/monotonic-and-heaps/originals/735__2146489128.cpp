class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        std::stack<int> s{};
        s.push(asteroids[0]);

        for (int i = 1; i < asteroids.size(); ++i) {
            bool broken = false;
            while (!s.empty() && asteroids[i] < 0 && s.top() > 0) {
                if (std::abs(s.top()) < std::abs(asteroids[i])) {
                    s.pop();
                } else if (std::abs(s.top()) == std::abs(asteroids[i])) {
                    s.pop();
                    broken = true;
                    break;
                } else {
                    broken = true;
                    break;
                }
            }

            if (!broken) {
                s.push(asteroids[i]);
            }
        }
        
        std::vector<int> result{};
        while (!s.empty()) {
            result.push_back(s.top());
            s.pop();
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
};