/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int pivot;
        int length = mountainArr.length();
        int left = 0; int right = length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int leftBound = mid > 0 ? mountainArr.get(mid - 1) : INT_MIN;
            int rightBound = mid < (length - 1) ? mountainArr.get(mid + 1) : INT_MIN;

            int midVal = mountainArr.get(mid);
            if (midVal > leftBound && midVal > rightBound) {
                pivot = mid;
                break;
            } else if (midVal > leftBound && midVal < rightBound) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        left = 0; right = pivot;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            int midV = mountainArr.get(mid);

            if (midV == target) {
                return mid;
            } else if (midV > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        left = pivot + 1; right = length - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midV = mountainArr.get(mid);

            if (midV == target) {
                return mid;
            } else if (midV > target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};