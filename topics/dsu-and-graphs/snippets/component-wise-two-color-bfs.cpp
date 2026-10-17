    bool isBipartite(vector<vector<int>>& graph) {
        std::vector<int> color(graph.size());

        for (int i = 0; i < graph.size(); i++) {
            if (color[i] == 0) {
                if (!coloring(graph, i, color)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool coloring(std::vector<std::vector<int>>& graph, int start, std::vector<int>& color) {
        std::deque<int> q{};
        q.push_back(start);
        color[start] = 1;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int current = q.front(); q.pop_front();
                
                for (int neighbor : graph[current]) {
                    if (color[current] == color[neighbor]) {
                        return false;
                    } else if (color[neighbor] == 0) {
                        if (color[current] == 1) {
                            color[neighbor] = 2;
                        } else {
                            color[neighbor] = 1;
                        }

                        q.push_back(neighbor);
                    }
                }
            }
        }

        return true;
    }
