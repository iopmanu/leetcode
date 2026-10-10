class Solution {
public:
    string reverseParentheses(string s) {
        std::deque<int> open{};
        std::string result{};

        for (int i = 0 ; i < s.size(); i++) {
            if (s[i] == '(') {
                open.push_back(result.length());
            } else if (s[i] == ')') {
                std::reverse(result.begin() + open.back(), result.end());
                open.pop_back();
            } else {
                result.push_back(s[i]);
            }
        }

        return result;
    }
};