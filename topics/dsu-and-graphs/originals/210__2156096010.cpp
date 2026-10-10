class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        std::unordered_map<int, std::vector<int>> adj{};
        std::vector<int> indegree(numCourses, 0);
        for (auto p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }

        std::deque<int> q{};
        for (int i = 0; i < indegree.size(); i++) {
            if (!indegree[i]) {
                q.push_back(i);
            }
        }

        std::vector<int> result{};
        while (!q.empty()) {
            auto currentSize = q.size();
            for (int i = 0; i < currentSize; i++) {
                int current = q.front(); q.pop_front();
                result.push_back(current);

                for (auto neighbor : adj[current]) {
                    indegree[neighbor]--;
                    if (!indegree[neighbor]) {
                        q.push_back(neighbor);
                    }
                }   
            }
        }

        return result.size() == numCourses ? result : std::vector<int>{};
    }
};