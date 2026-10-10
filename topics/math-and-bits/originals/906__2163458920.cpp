class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long long l = std::stoll(left); long long r = std::stoll(right);

        int result = 0;
        for (long long i = 0; i < 1e5; i++) {
            std::string current = std::to_string(i);
            std::string palindrome = current + reversed(current.substr(0, current.size() - 1));
            long long num = std::stoll(palindrome);
            long long square = num * num;

            if (square > r) {
                break;
            }

            if (square >= l && isPalindrome(square)) {
                ++result;
            }
        }

        for (long long i = 0; i < 1e5; i++) {
            std::string current = std::to_string(i);
            std::string palindrome = current + reversed(current.substr(0, current.size()));
            long long num = std::stoll(palindrome);
            long long square = num * num;

            if (square > r) {
                break;
            }

            if (square >= l && isPalindrome(square)) {
                ++result;
            }
        }

        return result;
    }

    bool isPalindrome(long long num) {
        long long ans = 0; long long copy = num;
        while (copy > 0) {
            ans = 10 * ans + copy % 10;
            copy /= 10;
        }

        return ans == num;
    }

    std::string reversed(const std::string& s) {
        std::string rev(s.size(), 'a');
        for (int i = s.size() - 1; i >= 0; i--) {
            rev[s.size() - i - 1] = s[i]; 
        }

        return rev;
    }
};