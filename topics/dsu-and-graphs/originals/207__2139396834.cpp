class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        if (prerequisites.empty()) {
            return true;
        }

        std::unordered_map<int, std::vector<int>> graph{};
        for (auto&& p : prerequisites) {
            graph[p[1]].push_back(p[0]);
        }

        std::unordered_map<int, bool> visiting{}, visited{};

        bool result = true;
        for (auto i = 0; i < numCourses; ++i) {
            result &= dfs(graph, visiting, visited, i);
        }

        return result;
    }

    bool dfs(auto& graph, auto& visiting, auto& visited, int current) {
        if (visited.contains(current)) {
            return true;
        }

        if (visiting.contains(current)) {
            return false;
        }

        visiting[current] = true;

        bool result = true;
        for (auto neighbor : graph[current]) {
            result &= dfs(graph, visiting, visited, neighbor);
        }

        visiting.erase(current);
        visited[current] = true;

        return result;
    }
};