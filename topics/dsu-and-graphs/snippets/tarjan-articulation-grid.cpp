class Solution {
    std::vector<int> disc;
    std::vector<int> low;
    std::vector<int> parent;
    int time = 0;

public:
    int minDays(vector<vector<int>>& grid) {
        int n = grid.size() * grid[0].size();
        disc.resize(n, -1); low.resize(n, -1); parent.resize(n, -1);

        std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        int articulationPoints = 0;
        std::function<void(int, int, int, int)> dfs = [&](int i, int j, int parentX, int parentY) {
            int key = i * grid[0].size() + j;
            if (key >= n) {
                return;
            }

            bool isArticulation = false;
            int children = 0;
            disc[key] = low[key] = time++;
            for (auto&& d : directions) {
                int newX = i + d[0]; int newY = j + d[1];
                int nKey = newX * grid[0].size() + newY;

                if (newX < 0 || newY < 0 || newX >= grid.size() || newY >= grid[0].size()) {
                    continue;
                }

                if (!grid[newX][newY] || nKey >= n) {
                    continue;
                }

                if (disc[nKey] == -1) {
                    parent[nKey] = key;
                    ++children;
                    dfs(newX, newY, parentX, parentY);

                    low[key] = std::min(low[key], low[nKey]);
                    if ((i != parentX || j != parentY) && low[nKey] >= disc[key]) {
                        isArticulation = true;;
                    }
                } else if (parent[key] != nKey) {
                    low[key] = std::min(low[key], disc[nKey]);
                }
            }

            if (i == parentX && j == parentY && children > 1) {
                isArticulation = true;
            }

            articulationPoints += (isArticulation == true);
        };

        int islands = 0;
        int landCount = 0;
        int rootX = -1; int rootY = -1;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                int key = i * grid[0].size() + j;
                if (grid[i][j]) {
                    ++landCount;
                    if (grid[i][j] && disc[key] == -1) {
                        ++islands;
                        dfs(i, j, i, j);
                    }
                }
            }
        }

        if (!islands || islands > 1) {
            return 0;
        }

        if (landCount <= 2) {
            return landCount;
        }

        if (articulationPoints > 0) {
            return 1;
        }

        return 2;
    }
};