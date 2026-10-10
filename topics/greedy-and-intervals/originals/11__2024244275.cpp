class Solution {
public:
    int maxArea(vector<int>& height) {
        size_t left = 0, right = height.size() - 1;

        int result = 0;
        while (left < right) {
            int square = std::min(height[right], height[left]) * (right - left);
            result = std::max(square, result);

            if (height[left] < height[right]) {
                ++left;
            } else {
                --right;
            }
        }

        return result;
    }
};