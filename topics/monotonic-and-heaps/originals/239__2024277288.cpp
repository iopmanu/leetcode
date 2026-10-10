class Solution {
    struct PairComparator {
        bool operator()(const std::pair<int,int>& a, const std::pair<int,int>& b) const {
            if (a.first != b.first) {
                return a.first < b.first;
            }
            return a.second > b.second;
        }
    };

    using TQueue = std::priority_queue<
                    std::pair<int, int>,
                    std::vector<std::pair<int, int>>,
                    PairComparator
                   >;

public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        TQueue q{};
        std::vector<int> result;

        for (int i = 0; i < k; ++i) {
            q.push({nums[i], i});
        }
        result.push_back(q.top().first);

        for (int i = k; i < nums.size(); ++i) {
            q.push({nums[i], i});

            while (!q.empty() && q.top().second <= (i - k)) {
                q.pop();
            }

            result.push_back(q.top().first);
        }

        return result;
    }
};