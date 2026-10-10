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
        int peak;
        int length = mountainArr.length();
        int left = 0; int right = length - 1;

        while (right - left > 2) {
            int lm = left + (right - left) / 3;
            int rm = right - (right - left) / 3;

            int lmv = mountainArr.get(lm);
            int rmv = mountainArr.get(rm);

            if (lmv < rmv) {
                left = lm;
            } else {
                right = rm;
            }
        }

        int pivot = left;

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