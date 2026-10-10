class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int current = INT_MAX;

        int result = 0;
        for (int i = 0; i < prices.size(); ++i) {
            current = std::min(current, prices[i]);
            result = std::max(result, prices[i] - current);
        }

        return result;
    }
};