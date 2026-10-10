class Solution {
public:
    int trap(vector<int>& height) {
        std::deque<int> ms;

        int result = 0;
        for (int i = 0; i < height.size(); ++i) {
            while (!ms.empty() && height[ms.back()] < height[i]) {
                auto mid = ms.back();
                ms.pop_back();
                if (ms.empty()) {
                    break;
                }

                auto minHeight = std::min(height[i] - height[mid], height[ms.back()] - height[mid]);
                result += minHeight * (i - ms.back() - 1);
            }

            ms.push_back(i);
        }

        return result;
    }
};