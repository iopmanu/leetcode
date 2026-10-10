class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int left = 0; int right = matrix.size() * matrix[0].size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            int i = mid / matrix[0].size();
            int j = mid % matrix[0].size();
            
            if (matrix[i][j] == target) {
                return true;
            } else if (matrix[i][j] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return false;
    }
};