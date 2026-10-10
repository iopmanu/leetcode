class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        std::deque<int> ms{};

        int result = 0;
        for (int i = 0; i < heights.size(); ++i) {
            while (!ms.empty() && heights[ms.back()] > heights[i]) {
                auto idx = ms.back();
                ms.pop_back();

                auto left = ms.empty() ? -1 : ms.back();
                auto width = i - left - 1;

                result = std::max(result, width * heights[idx]);
            }
            
            ms.push_back(i);
        }

        while (!ms.empty()) {
            auto idx = ms.back();
            ms.pop_back();

            auto left = ms.empty() ? -1 : ms.back();
            int width = heights.size() - left - 1;

            result = std::max(result, width * heights[idx]);
        }

        return result;
    }
};