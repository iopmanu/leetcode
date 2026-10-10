class Solution {
public:
    string decodeString(string s) {
        std::ostringstream os{};

        int multiplier = 0;
        std::stack<std::string> st{};
        std::stack<int> multipliers{};

        std::string current = "";
        for (int i = 0; i < s.size(); ++i) {
            if (std::isdigit(s[i])) {
                multiplier = multiplier * 10 + (s[i] - '0');
            } else if (s[i] == '[') {
                multipliers.push(multiplier);
                multiplier = 0;
                st.push(current);
                current = "";
            } else if (s[i] == ']') {
                string tmp = current;
                current = st.top();
                st.pop();
                int repeat = multipliers.top();
                multipliers.pop();
                while (repeat--) {
                    current += tmp;
                }
            } else {
                current += s[i];
            }
        }

        return current;
    }
};