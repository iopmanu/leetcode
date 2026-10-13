class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size(); int m = grid[0].size();

        if (grid[0][0] == 1 || grid[n - 1][m - 1] == 1) {
            return -1;
        }

        std::deque<std::pair<int, int>> cells{};
        cells.push_back(std::make_pair(0, 0));
        grid[0][0] = 1;

        std::vector<std::vector<int>> directions{};
        for (int i : std::vector<int>{-1, 0, 1}) {
            for (int j : std::vector<int>{-1, 0, 1}) {
                if (i != 0 || j != 0) {
                    directions.push_back({i, j});
                }
            }
        }
        
        int path = 1;
        while (!cells.empty()) {
            int size = cells.size();
            for (int k = 0; k < size; k++) {
                int i = cells.front().first; int j = cells.front().second;
                cells.pop_front();

                if (i == n - 1 && j == m - 1) {
                    return path;
                }

                for (auto&& dir : directions) {
                    int newI = i + dir[0]; int newJ = j + dir[1];

                    if (newI >= n || newJ >= m || newI < 0 || newJ < 0) {
                        continue;
                    }

                    if (grid[newI][newJ] == 1) {
                        continue;
                    }

                    cells.push_back(std::make_pair(newI, newJ));
                    grid[newI][newJ] = 1;
                }
            }

            ++path;
        }

        return -1;
    }
};