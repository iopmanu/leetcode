class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits_array;
        
        for (int i = 0; i <= n; i++) {
            int counter = 0;
            int copy = i;

            while (copy != 0) {
                if (copy % 2 == 1)
                    counter++;
                copy /= 2;
            }

            bits_array.push_back(counter);
        }
        
        return bits_array;
    }
};