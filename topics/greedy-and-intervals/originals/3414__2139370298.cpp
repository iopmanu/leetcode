class Solution {
    struct State {
        long long score = 0;
        std::vector<int> path{};
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // keep original index after sorting
        for (int i = 0; i < n; ++i) {
            intervals[i].push_back(i);
        }

        // sort by right endpoint
        std::sort(
            intervals.begin(),
            intervals.end(),
            [](const auto& l, const auto& r) {
                if (l[1] != r[1]) {
                    return l[1] < r[1];
                }

                if (l[0] != r[0]) {
                    return l[0] < r[0];
                }

                return l[3] < r[3];
            }
        );

        // prev[i] = largest index j:
        // intervals[j].right < intervals[i].left
        std::vector<int> prev(n, -1);

        for (int i = 0; i < n; ++i) {
            int left = 0;
            int right = i;

            while (left < right) {
                int mid = left + (right - left) / 2;

                if (intervals[mid][1] < intervals[i][0]) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            if (left < i && intervals[left][1] < intervals[i][0]) {
                prev[i] = left;
            } else {
                prev[i] = left - 1;
            }
        }

        // dp[k][i]:
        // best state using up to k intervals
        // among first i sorted intervals
        std::vector<std::vector<State>> dp(
            5,
            std::vector<State>(n + 1)
        );

        for (int i = 1; i <= n; ++i) {
            int current = i - 1;

            for (int k = 1; k <= 4; ++k) {
                // don't take current
                State skip = dp[k][i - 1];

                // take current
                State take = dp[k - 1][prev[current] + 1];
                take.score += intervals[current][2];
                take.path.push_back(intervals[current][3]);

                // indices in answer must be lexicographically compared
                // by original indices, not by interval ending time
                std::sort(take.path.begin(), take.path.end());

                dp[k][i] = better(skip, take);
            }
        }

        return dp[4][n].path;
    }

private:
    State better(const State& l, const State& r) {
        if (l.score != r.score) {
            return l.score > r.score ? l : r;
        }

        return l.path < r.path ? l : r;
    }
};