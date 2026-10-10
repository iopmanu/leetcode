class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0; int right = height.size() - 1;
        int result = 0;
        int maxHeight = 0;

        while (left < right) {
            int minHeight = std::min(height[left], height[right]);
            maxHeight = std::max(maxHeight, minHeight);

            result += maxHeight - minHeight;
            if (height[left] > height[right]) {
                --right;
            } else {
                ++left;
            }
        }

        return result;
    }
};