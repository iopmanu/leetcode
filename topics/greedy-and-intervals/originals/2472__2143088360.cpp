class Solution {
public:
    int maxPalindromes(string s, int k) {
        int result = 0;

        for (int i = 0; i <= s.size() - k; ++i) {
            for (int len = k; len <= k + 1; ++len) {
                if (i + len > s.size()) {
                    continue;
                }

                int start = i;
                int end = i + len - 1;

                bool isPalindrome = true;
                while (start < end) {
                    if (s[start++] != s[end--]) {
                        isPalindrome = false;
                        break;
                    }
                }

                if (isPalindrome) {
                    ++result;
                    i += len - 1;
                    break;
                }
            }
        }

        return result;
    }
};