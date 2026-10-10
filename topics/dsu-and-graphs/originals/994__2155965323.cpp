class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(); int m = grid[0].size();

        std::deque<std::pair<int, int>> q{};
        int freshes = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push_back(std::make_pair(i, j));
                }
                
                freshes += (grid[i][j] == 1);
            }
        }

        if (freshes == 0) {
            return 0;
        }

        if (q.empty()) {
            return -1;
        }

        int time = -1;
        std::vector<std::pair<int, int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        while (!q.empty()) {
            int currentSize = q.size();

            for (int i = 0; i < currentSize; i++) {
                auto [x, y] = q.front();
                q.pop_front();

                for (auto [dx, dy] : dirs) {
                    auto newX = x + dx; auto newY = y + dy;
                    if (newX >= 0 && newX < n && newY >= 0 && newY < m && grid[newX][newY] == 1) {
                        grid[newX][newY] = 2;
                        q.push_back(std::make_pair(newX, newY));
                        freshes--;
                    }
                }
            }

            ++time;
        }

        return freshes == 0 ? time : -1;
    }
};