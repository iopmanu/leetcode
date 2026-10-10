class Solution {
public:
    int longestValidParentheses(string s) {
        std::deque<int> stk{};
        stk.push_back(-1);
        int result = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                stk.push_back(i);
            } else {
                stk.pop_back();

                if (stk.empty()) {
                    stk.push_back(i);
                } else {
                    result = max(i - stk.back(), result);
                }
            }
        }

        return result;
    }
};