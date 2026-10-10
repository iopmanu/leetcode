class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // Ensure nums1 is the smaller array for simplicity
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        int x = nums1.size();
        int y = nums2.size();
        int low = 0;
        int high = x;
        
        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (x + y + 1) / 2 - partitionX;
            
            // If partitionX is 0, use -INF for maxX
            // If partitionX is x, use INF for minX
            int maxX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minX = (partitionX == x) ? INT_MAX : nums1[partitionX];
            
            int maxY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minY = (partitionY == y) ? INT_MAX : nums2[partitionY];
            
            if (maxX <= minY && maxY <= minX) {
                // Found the correct partition
                // If total length is odd
                if ((x + y) % 2 != 0) {
                    return max(maxX, maxY);
                } else {
                    // If total length is even
                    return (max(maxX, maxY) + min(minX, minY)) / 2.0;
                }
            } else if (maxX > minY) {
                // Move partition to the left
                high = partitionX - 1;
            } else {
                // Move partition to the right
                low = partitionX + 1;
            }
        }
        
        // Should never reach here
        return 0.0;
    }
};
