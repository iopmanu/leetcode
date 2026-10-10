class Solution {
    using TQueue = std::priority_queue<std::vector<int>>;

public:
    vector<int> findClosestElements(vector<int>& nums, int k, int x) {
        TQueue diffs{};
        for (int i = 0; i < nums.size(); ++i) {
            diffs.push(std::vector<int>{std::abs(nums[i] - x), nums[i]});

            if (diffs.size() > k) {
                diffs.pop();
            }
        }

        std::vector<int> result{};
        while (!diffs.empty()) {
            result.push_back(diffs.top()[1]);
            diffs.pop();
        }

        std::sort(result.begin(), result.end());
        return result;
    }
};