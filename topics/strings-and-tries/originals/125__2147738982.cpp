class Solution {
public:
    char toLower(char a) {
        if (a <= 'Z') {
            return a - 'A' + 'a';
        }

        return a;
    }

    bool isPalindrome(string s) {
        int left = 0; int right = s.size() - 1;
        while (left < right) {
            if (!std::isalnum(s[left])) {
                ++left;
            } else if (!std::isalnum(s[right])) {
                --right;
            } else if (toLower(s[left]) == toLower(s[right])) {
                left++;
                right--;
            } else {
                return false;
            }
        }

        return true;
    }
};