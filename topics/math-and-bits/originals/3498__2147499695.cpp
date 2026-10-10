class Solution {
public:
    int reverseDegree(string s) {
        int sum = 0;
        for (int i = 0; i < s.size(); i++) {
            std::cout << s[i] << " " << int('z' - s[i] + 1);
            sum += ('z' - s[i] + 1) * (i + 1);
        }

        return sum;
    }
};