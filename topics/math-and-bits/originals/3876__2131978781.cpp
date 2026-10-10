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

        return minOdd == INT_MAX || minOdd < minEven;
    }
};