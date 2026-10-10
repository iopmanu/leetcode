#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size(); // Исправлено: берем n как размер строки

        // Вспомогательный лямбда-выражение для характеристик ячейки
        auto get_stats = [](int val) -> pair<int, int> {
            if (val == 0) return {0, 0};
            if (val == 1) return {1, 1};
            return {2, 1}; // val == 2
        };

        // Таблица DP: dp[r][c][cost] = max_score
        // Инициализируем значением -1 (недостижимо)
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, -1)));

        // Инициализация стартовой позиции
        auto [start_score, start_cost] = get_stats(grid[0][0]);
        if (start_cost <= k) {
            dp[0][0][start_cost] = start_score;
        } else {
            return -1; // Если даже старт не влезает в бюджет
        }

        // Обходим сетку строго по порядку (слева направо, сверху вниз)
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                
                // Получаем параметры текущей ячейки
                auto [cell_score, cell_cost] = get_stats(grid[r][c]);

                for (int cost = 0; cost <= k; ++cost) {
                    // Если текущее состояние недостижимо, пропускаем
                    if (dp[r][c][cost] == -1) continue;

                    // Пытаемся пойти ВПРАВО
                    if (c + 1 < n) {
                        auto [next_score, next_cost_gain] = get_stats(grid[r][c + 1]);
                        int next_cost = cost + next_cost_gain;
                        if (next_cost <= k) {
                            dp[r][c + 1][next_cost] = max(dp[r][c + 1][next_cost], dp[r][c][cost] + next_score);
                        }
                    }

                    // Пытаемся пойти ВНИЗ
                    if (r + 1 < m) {
                        auto [next_score, next_cost_gain] = get_stats(grid[r + 1][c]);
                        int next_cost = cost + next_cost_gain;
                        if (next_cost <= k) {
                            dp[r + 1][c][next_cost] = max(dp[r + 1][c][next_cost], dp[r][c][cost] + next_score);
                        }
                    }
                }
            }
        }

        // Ищем максимум в конечной ячейке
        int ans = -1;
        for (int cost = 0; cost <= k; ++cost) {
            ans = max(ans, dp[m - 1][n - 1][cost]);
        }

        return ans;
    }
};
