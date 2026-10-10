class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        std::deque<int> positions{};

        std::vector<int> prefixes(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefixes[i + 1] = prefixes[i] + nums[i];
        }

        int result = INT_MAX;
        for (int i = 0; i <= nums.size(); i++) {
            while (!positions.empty() && prefixes[i] - prefixes[positions.back()] >= k) {
                result = std::min(result, i - positions.back());
                positions.pop_back();
            }

            while (!positions.empty() && prefixes[i] <= prefixes[positions.front()]) {
                positions.pop_front();
            }

            positions.push_front(i);
        }

        return result == INT_MAX ? -1 : result;
    }
};