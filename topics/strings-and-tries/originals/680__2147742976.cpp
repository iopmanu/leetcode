class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0; int right = s.size() - 1;
        
        bool deleted = false;
        while (left < right) {
            if (s[left] != s[right]) {
                return isPalindrome(left + 1, right, s) | isPalindrome(left, right - 1, s);
            } else {
                left++;
                right--;
            }
        }

        return true;
    }

    bool isPalindrome(int left, int right, std::string& s) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }

        return true;
    }
};