class Solution {
public:
    string firstPalindrome(vector<string>& words) {
        bool is_found = 0;
        int i = 0;
        
        for (i = 0; i < words.size() && !is_found; i++) {
            if (is_palindrom(words[i])) {
                is_found = 1;
            }
        }
        
        if (is_found == 1) {
            return words[i - 1];
        } else {
            return "";
        }
    }
    
    
    bool is_palindrom(const string& source) {
        for (int i = 0; i < source.size() / 2; i++) {
            if (source[i] != source[source.size() - i - 1])
                return false;
        }
        return true;
    }
};