class Solution {
public:
    int myAtoi(string s) {
        int i = 0;
        int n = s.size();

        while (i < n && s[i] == ' ') {
            ++i;
        }

        if (i == n) {
            return 0;
        }

        int sign = 1;

        if (s[i] == '-' || s[i] == '+') {
            sign = (s[i] == '-') ? -1 : 1;
            ++i;
        }

        long long result = 0;
        long long limit = sign == -1
            ? -static_cast<long long>(INT_MIN)
            : static_cast<long long>(INT_MAX);

        while (i < n && s[i] >= '0' && s[i] <= '9') {
            int digit = s[i] - '0';

            if (result > (limit - digit) / 10) {
                return sign == -1 ? INT_MIN : INT_MAX;
            }

            result = result * 10 + digit;
            ++i;
        }

        return static_cast<int>(sign * result);
    }
};