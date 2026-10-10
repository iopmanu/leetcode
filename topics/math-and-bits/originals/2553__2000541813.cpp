class Solution {
public:
    std::vector<int> separateDigits(std::vector<int>& nums) {
        std::vector<int> result;
        for (auto num : nums) {
            std::deque<int> q;
            while (num != 0) {
                q.push_back(num % 10);
                num /= 10;
            }

            while (!q.empty()) {
                result.push_back(q.back());
                q.pop_back();
            }
        }

        return result;
    }
};