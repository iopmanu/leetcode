class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0; int right = height.size() - 1;
        int maxL = height[left]; int maxR = height[right];

        int result = 0;
        while (left <= right) {
            maxL = std::max(height[left], maxL);
            maxR = std::max(height[right], maxR);

            auto minHeight = std::min(maxL, maxR);
            result += minHeight - std::min(height[left], height[right]);

            if (height[left] < height[right]) {
                ++left;
            } else {
                --right;
            }
        }

        return result;
    }
};