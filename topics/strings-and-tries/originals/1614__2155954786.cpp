class Solution {
public:
    int maxDepth(string s) {
        int result = 0;
        int current = 0;
        for (auto ch : s) {
            current += (ch == '(');
            current -= (ch == ')');
            result = max(result, current);
        }

        return result;
    }
};