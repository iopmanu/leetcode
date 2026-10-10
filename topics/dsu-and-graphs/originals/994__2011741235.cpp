class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        int freshes = 0;
        std::queue<std::pair<int, int>> q;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    ++freshes;
                } else if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }

        if (freshes == 0) {
            return 0;
        }
        if (q.empty()) {
            return -1;
        }

        int minutes = -1;
        std::vector<std::pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [x, y] = q.front();
                q.pop();
                for (auto [dx, dy] : dirs) {
                    int i = x + dx;
                    int j = y + dy;

                    if (i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 1) {
                        grid[i][j] = 2;
                        --freshes;
                        q.push({i, j});
                    }
                }
            }

            minutes++;
        }

        if (freshes == 0) {
            return minutes;
        }

        return -1;
    }
};