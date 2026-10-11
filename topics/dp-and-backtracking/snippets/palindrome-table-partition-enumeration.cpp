    vector<vector<string>> partition(string s) {
        std::vector<std::vector<bool>> isPalindrome(s.size(), std::vector<bool>(s.size(), false));
        for (int r = 0; r < s.size(); r++) {
            for (int l = 0; l <= s.size(); l++) {
                if (s[l] == s[r] && (r - l <= 2 || isPalindrome[l+1][r-1])) {
                    isPalindrome[l][r] = true;
                }
            }
        }

        std::vector<std::vector<std::string>> result{};
        std::function<void(int, std::vector<std::string>&)> recursive = [&] (int i, std::vector<std::string>& path) {
            if (i == s.size()) {
                result.push_back(path);
                return;
            }

            for (int right = i; right < s.size(); right++) {
                if (isPalindrome[i][right]) {
                    path.push_back(s.substr(i, right - i + 1));
                    recursive(right + 1, path);
                    path.pop_back();
                }
            }
        };

        std::vector<std::string> buff{};
        recursive(0, buff);

        return result;
    }
