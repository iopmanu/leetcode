class Solution {
public:
    int maxDistToClosest(vector<int>& row) {
        // support variables
        size_t left = -1, right = 0;     
        size_t result = 0;

        while (right < row.size()) {
            if (row[right] && left == -1) {
                result = max(result, right);
                left = right;
                right += 1;
                continue;
            }

            if (right == row.size() - 1 && !row[right]) {
                result = max(result, right - left);
                right += 1;
                continue;
            }

            if (row[right]) {
                result = max(result, (right - left) / 2);
                left = right;
            }

            right += 1;
        }

        return result;
    }
};