class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0; int right = height.size() - 1;
        int leftMax = INT_MIN; int rightMax = INT_MIN;

        int result = 0;
        while (left < right) {
            leftMax = std::max(height[left], leftMax);
            rightMax = std::max(height[right], rightMax);
            int currentHeight = std::min(height[left], height[right]);

            result += std::min(leftMax, rightMax) - currentHeight;
            if (height[left] > height[right]) {
                right--;
            } else {
                left++;
            }
        }

        return result;
    }
};