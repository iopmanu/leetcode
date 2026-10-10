class Solution {
public:
    vector<bool> checkIfPrerequisite(
        int numCourses, 
        vector<vector<int>>& prerequisites, 
        vector<vector<int>>& queries
    ) {
        std::unordered_map<int, std::vector<int>> adj{};
        for (auto p : prerequisites) {
            adj[p[0]].push_back(p[1]);
        }

        std::vector<std::vector<int>> reachable(numCourses, std::vector<int>(numCourses, 0));
        for (int i = 0; i < numCourses; i++) {
            std::deque<int> q{};
            q.push_back(i);

            while (!q.empty()) {
                auto currentSize = q.size();
                for (int j = 0; j < currentSize; j++) {
                    int current = q.front(); q.pop_front();
                    reachable[i][current] = 1;
                    
                    for (int neighbor : adj[current]) {
                        q.push_back(neighbor);
                    }
                }
            }
        }

        std::vector<bool> result{};
        for (auto q : queries) {
            result.push_back(static_cast<bool>(reachable[q[0]][q[1]]));
        }

        return result;
    }
};