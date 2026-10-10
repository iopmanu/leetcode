class Solution {
public:
    int minInsertions(string s) {
        int i = 0; int changes = 0;
        int open = 0;
        while (i < s.size()) {
            if (s[i] == ')') {
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    ++i;
                } else {
                    ++changes;
                }

                if (open > 0) {
                    --open;
                } else {
                    ++changes;
                }
            } else {
                ++open;
            }

            i++;
        }

        changes += open * 2;
        return changes;
    }
};