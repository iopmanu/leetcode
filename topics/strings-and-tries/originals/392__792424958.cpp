class Solution {
public:
    bool isSubsequence(string s, string t) {
        int s_length = s.length();
        int t_length = t.length();
        int j = 0;
        
        for (int i = 0; i < t_length; i++) {
            if (s[j] == t[i])
                j++;
        }
        
        if (j == s_length) {
            return true;
        }
        
        return false;
    }
};