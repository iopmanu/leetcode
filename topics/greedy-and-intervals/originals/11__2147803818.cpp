class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0; int right = height.size() - 1;

        int result = 0;
        while (left < right) {
            int width = right - left;
            result = std::max(result, width * std::min(height[left], height[right]));

            if (height[left] > height[right]) {
                right--;
            } else {
                left++;
            }
        }

        return result;
    }
};