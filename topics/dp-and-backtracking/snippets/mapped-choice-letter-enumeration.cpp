class Solution {
    std::unordered_map<char, std::vector<char>> letters {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };

public:
    vector<string> letterCombinations(string digits) {
        std::vector<std::string> result{};
        std::function<void(int i, std::string&)> dfs = [&](int i, std::string& buff) {
            if (i == digits.size()) {
                result.push_back(buff);
                return;
            }

            for (char n : letters[digits[i]]) {
                buff.push_back(n);
                dfs(i + 1, buff);
                buff.pop_back();
            }
        };

        std::string buff{};
        dfs(0, buff);
        return result;
    }
};