class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> pascal_triangle = {{ 1 }};
        
        feel_row(pascal_triangle, numRows, 0);
        

        
        
        return pascal_triangle;
    }
    
    void feel_row(vector<vector<int>> &pascal_triangle, int numRows, int currentRow) {
        if (currentRow == numRows - 1) {
            return;
        }
        
        vector<int> current_vector = pascal_triangle[currentRow];
        vector<int> next_row;
        
        next_row.push_back(1);
        
        for (int i = 0; i <= currentRow - 1; i++) {
            next_row.push_back(current_vector[i] + current_vector[i + 1]);
        }
        
        next_row.push_back(1);
        
        pascal_triangle.push_back(next_row);
        feel_row(pascal_triangle, numRows, currentRow + 1);
    }
};