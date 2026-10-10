// odd - odd = odd
// odd - even = even
// even - odd = even
// even - even = odd

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minOdd = INT_MAX, minEven = INT_MAX;
        for (auto num : nums1) {
            if (num % 2) {
                minOdd = std::min(minOdd, num);
            } else {
                minEven = std::min(minEven, num);
            }
        }

        if (minOdd != INT_MAX) {
            for (auto num : nums1) {
                if (!(num % 2) && num - minOdd < 1) {
                    return false;
                }
            }
        } else {
            for (auto num : nums1) {
                if (num % 2 && num - minEven < 1) {
                    return false;
                }
            }
        }

        return true;
    }
};