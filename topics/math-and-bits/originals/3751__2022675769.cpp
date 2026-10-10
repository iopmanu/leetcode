class Solution {
public:
    int totalWaviness(int num1, int num2) {
        int result = 0;
        for (int i = num1; i <= num2; ++i) {
            result += waviness(i);
        }
        
        return result;
    }

    int waviness(int x) {
        std::string s = std::to_string(x);
        int waviness = 0;

        for (int i = 1; i < s.size() - 1; i++) {
            if ((s[i] > s[i - 1] && s[i] > s[i + 1]) ||
                (s[i] < s[i - 1] && s[i] < s[i + 1])) {
                    ++waviness;
                }
        }

        return waviness;
    }


};