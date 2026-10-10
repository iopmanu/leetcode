class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0; int right = height.size() - 1;

        int result = 0;
        while (left < right) {
            result = std::max(result, std::min(height[right], height[left]) * (right - left));
            if (height[left] < height[right]) {
                ++left;
            } else {
                --right;
            }
        }

        return result;
    }
};