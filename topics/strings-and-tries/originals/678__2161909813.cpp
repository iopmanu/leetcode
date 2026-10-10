class Solution {
public:
    bool checkValidString(string s) {
        int open = 0;
        int close = 0;
        int length = s.size() - 1;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '*') {
                ++open;
            } else {
                --open;
            }

            if (s[length - i] == ')' || s[length - i] == '*') {
                ++close;
            } else {
                --close;
            }

            if (close < 0 || open < 0) {
                return false;
            }
        }

        return true;
    }
};