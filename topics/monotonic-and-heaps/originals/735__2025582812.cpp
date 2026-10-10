class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        std::deque<int> q;
        for (int i = 0; i < asteroids.size(); i++) {
            bool destroyed = false;
            while (!q.empty() && asteroids[i] < 0) {
                if (q.back() < 0) {
                    break;
                }

                int compare = -asteroids[i];

                if (q.back() < compare) {
                    q.pop_back();
                } else if (q.back() > compare) {
                    destroyed = true;
                    break;
                } else if (q.back() == compare) {
                    q.pop_back();
                    destroyed = true;
                    break;
                }
            }

            if (!destroyed) {
                q.push_back(asteroids[i]);
            }
        }

        return {q.begin(), q.end()};
    }
};