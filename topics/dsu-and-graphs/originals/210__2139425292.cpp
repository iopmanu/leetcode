class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        std::unordered_map<int, std::vector<int>> adj{};
        std::vector<int> inDegree(numCourses, 0);
        for (const auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]);
            ++inDegree[prereq[0]];
        }

        std::deque<int> q{};
        for (int i = 0; i < numCourses; ++i) {
            if (!inDegree[i]) {
                q.push_back(i);
            }
        }

        std::vector<int> result{};
        while (!q.empty()) {
            auto course = q.front();
            q.pop_front();
            result.push_back(course);

            for (auto neighbor : adj[course]) {
                if (--inDegree[neighbor] == 0) {
                    q.push_back(neighbor);
                }
            }
        }

        return result.size() != numCourses ? std::vector<int>{} : result;
    }
};