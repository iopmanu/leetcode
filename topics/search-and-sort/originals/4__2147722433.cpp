class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int x = nums1.size(); int y = nums2.size();
        if (x > y) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int left = 0; int right = x;

        while (left <= right) {
            int partitionX = left + (right - left) / 2;
            int partitionY = (x + y + 1) / 2 - partitionX;

            int maxX = partitionX == 0 ? INT_MIN : nums1[partitionX - 1];
            int minX = partitionX == x ? INT_MAX : nums1[partitionX];

            int maxY = partitionY == 0 ? INT_MIN : nums2[partitionY - 1];
            int minY = partitionY == y ? INT_MAX : nums2[partitionY];

            if (maxX <= minY && maxY <= minX) {
                if ((x + y) % 2 != 0) {
                    return std::max(maxX, maxY);
                } else {
                    return (std::max(maxX, maxY) + std::min(minX, minY)) / 2.0;
                }
            } else if (maxX > minY) {
                right = partitionX - 1;
            } else {
                left = partitionX + 1;
            }
        }

        return -1;
    }
};
