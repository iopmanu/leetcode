class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::unordered_map<int, std::vector<int>> adj{};
        std::vector<int> indegree(numCourses, 0);
        for (auto&& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            ++indegree[p[0]];
        }

        std::deque<int> q{};
        for (int i = 0; i < indegree.size(); i++) {
            if (!indegree[i]) {
                q.push_back(i);
            }
        }

        while (!q.empty()) {
            int currentSize = q.size();
            for (int i = 0; i < currentSize; i++) {
                int current = q.front(); q.pop_front();

                for (auto neighbor : adj[current]) {
                    int degree = --indegree[neighbor];
                    if (!degree) {
                        q.push_back(neighbor);
                    }
                }
            }
        }

        for (auto i : indegree) {
            if (i > 0) {
                return false;
            }
        }

        return true;
    }
};