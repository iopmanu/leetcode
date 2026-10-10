class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        std::stack<int> ms{};
        int result = 0;
        for (int i = 0; i < heights.size(); ++i) {
            while (!ms.empty() && heights[ms.top()] > heights[i]) {
                int pivot = ms.top();
                ms.pop();

                int left = ms.empty() ? -1 : ms.top();
                result = std::max(heights[pivot] * (i - left - 1), result);
            }

            ms.push(i);
        }

        int n = heights.size();
        while (!ms.empty()) {
            int pivot = ms.top();
            ms.pop();

            int left = ms.empty() ? -1 : ms.top();
            result = std::max(heights[pivot] * (n - left - 1), result);
        }

        return result;
    }
};