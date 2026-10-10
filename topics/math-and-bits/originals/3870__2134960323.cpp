class Solution {
public:
    int countCommas(int n) {
        int result = 0;
        for (int i = 1000; i <= n; i *= 1000) {
            result += (n - i + 1); 
            n /= 1000;
        }

        return result;
    }
};