class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        using TPair = std::pair<int, int>;
        std::priority_queue<TPair, std::vector<TPair>, std::greater<>> pq{};
        int result = INT_MAX;

        int current = 0;
        for (int i = 0; i < nums.size(); i++) {
            current += nums[i];
            if (current >= k) {
                result = std::min(result, i - 0 + 1);
            }

            while (!pq.empty() && current - pq.top().first >= k) {
                result = std::min(result, i - pq.top().second);
                pq.pop();
            }

            pq.push(std::make_pair(current, i));
        }

        return result == INT_MAX ? -1 : result;
    }
};