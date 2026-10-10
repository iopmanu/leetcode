class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        using TPair = std::pair<int, int>;
        std::priority_queue<TPair, std::vector<TPair>, std::greater<>> pq{};

        int current = 0; int result = INT_MAX;
        for (int i = 0; i < nums.size(); i++) {
            current += nums[i];
            if (current >= k) {
                result = std::min(result, i - 0 + 1);
            }

            while (!pq.empty() && current - pq.top().first >= k) {
                result = std::min(i - pq.top().second, result);
                pq.pop();
            }

            pq.push(std::make_pair(current, i));
        }

        return result == INT_MAX ? -1 : result;
    }
};