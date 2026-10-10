class Solution {
    
public:
    int minCut(string s) {
        std::vector<std::vector<bool>> isPalindrome(s.size(), std::vector<bool>(s.size(), false));
        for (int r = 0; r < s.size(); ++r) {
            for (int l = 0; l <= r; ++l) {
                if (s[l] == s[r] && (r - l <= 2 || isPalindrome[l+1][r-1])) {
                    isPalindrome[l][r] = true;
                }
            }
        }

        std::vector<int> memo(s.size(), -1);

        std::function<int(int)> recursive = [&](int i) {
            if (i == s.size()) {
                return -1;
            }

            if (memo[i] != -1) {
                return memo[i];
            }

            int minCuts = INT_MAX;
            for (int r = i; r < s.size(); ++r) {
                if (isPalindrome[i][r]) {
                    minCuts = std::min(minCuts, 1 + recursive(r + 1));
                }
            }

            return memo[i] = minCuts;
        };

        return recursive(0);
    }
};