class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits_array(n + 1);
        bits_array[0] = 0;
        
        for (int i = 0; i <= n; i++) {
            bits_array[i] = bits_array[i / 2] + i % 2;
        }
        
        
        return bits_array;
    }
};