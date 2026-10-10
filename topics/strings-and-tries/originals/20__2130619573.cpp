class Solution {
public:
    bool isValid(string s) {
        std::deque<char> symbols{};
        std::unordered_map<char, char> pairs{
            {'{', '}'}, {'[', ']'}, {'(', ')'}
        };

        for (int i = 0; i < s.size(); ++i) {
            if (pairs.contains(s[i])) {
                symbols.push_front(s[i]);
                continue;
            }

            for (const auto& [k, v] : pairs) {
                if (symbols.empty() || s[i] == v && k != symbols.front()) {
                    return false;
                }
            }

            symbols.pop_front();
        }

        return symbols.empty();
    }
};