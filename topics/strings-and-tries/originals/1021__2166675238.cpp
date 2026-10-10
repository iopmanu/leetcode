class Solution {
public:
    string removeOuterParentheses(string s) {
        int open = 0;
        std::ostringstream result;
        for (auto ch : s) {
            if (ch == ')') {
                --open;
            }

            if (open) {
                result << ch;
            }
            
            if (ch == '(') {
                ++open;
            }
        }

        return result.str();
    }
};