class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        std::deque<int> ms{};

        int result = 0;
        for (int i = 0; i < heights.size(); ++i) {
            while (!ms.empty() && heights[ms.back()] > heights[i]) {
                int idx = ms.back();
                ms.pop_back();

                int left = ms.empty() ? -1 : ms.back();
                int width = i - left - 1;

                result = std::max(result, heights[idx] * width);
            }

            ms.push_back(i);
        }

        while (!ms.empty()) {
            int idx = ms.back();
            ms.pop_back();

            int left = ms.empty() ? -1 : ms.back();
            int width = heights.size() - left - 1;

            result = std::max(result, width * heights[idx]);
        }

        return result;
    }
};