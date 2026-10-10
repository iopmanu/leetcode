class Solution {
public:
    int scoreOfParentheses(string s) {
        std::deque<int> st{};
        st.push_back(0);

        for (char ch : s) {
            if (ch == '(') {
                st.push_back(0);
            } else {
                int inside = st.back();
                st.pop_back();

                if (inside == 0) {
                    int below = st.back();
                    st.pop_back();
                    st.push_back(below + 1);
                } else {
                    int below = st.back();
                    st.pop_back();
                    st.push_back(below + 2 * inside);
                }
            }
        }

        return st.back();
    }
};