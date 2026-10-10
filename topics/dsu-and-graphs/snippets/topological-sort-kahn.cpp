    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        std::unordered_map<int, std::vector<int>> adj{};
        std::vector<int> indegree(numCourses, 0);

        for (const auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            ++indegree[p[0]];
        }

        std::deque<int> q{};
        for (int i = 0; i < indegree.size(); ++i) {
            if (!indegree[i]) {
                q.push_back(i);
            }
        }
        
        int count = 0;
        while (!q.empty()) {
            auto course = q.front();
            q.pop_front();
            ++count;
            
            for (auto neighbor : adj[course]) {
                if (--indegree[neighbor] == 0) {
                    q.push_back(neighbor);
                }
            }
        }

        return count == numCourses;
    }