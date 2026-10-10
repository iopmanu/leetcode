class Solution {
public:
    bool isValid(string s) {
        std::deque<char> symbols{};
        std::unordered_map<char, char> pairs{
            {'{', '}'}, {'[', ']'}, {'(', ')'}
        };

        for (auto ch : s) {
            if (pairs.contains(ch)) {
                symbols.push_back(ch);
                continue;
            }

            if (symbols.empty()) {
                return false;
            }

            for (auto [k, v] : pairs) {
                if (ch == v && symbols.back() != k) {
                    return false;
                }
            }

            symbols.pop_back();
        }

        return symbols.empty();
    }
};