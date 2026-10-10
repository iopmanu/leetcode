class Solution {
public:
    int longestValidParentheses(string s) {
        std::stack<int> stk;
        stk.push(-1);
        int max_len = 0;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();

                if (stk.empty()) {
                    stk.push(i);
                } else {
                    max_len = std::max(max_len, i - stk.top());
                }
            }
        }

        return max_len;
    }
};