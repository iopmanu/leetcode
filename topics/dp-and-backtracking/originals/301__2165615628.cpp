class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        std::vector<std::vector<std::unordered_set<std::string>>> memo(
            s.size() + 1, std::vector<std::unordered_set<std::string>>(s.size() + 1)
        );
        std::function<std::unordered_set<std::string>(int, int)> recursive = [&](int i, int open) {
            std::unordered_set<std::string> result{};
            if (open < 0) {
                return result;
            }

            if (!memo[i][open].empty()) {
                return memo[i][open];
            }

            if (i == s.size()) {
                if (open == 0) {
                    result.insert("");
                }

                return memo[i][open] = result;
            }

            if (s[i] == '(' || s[i] == ')') {
                const auto& skip = recursive(i + 1, open);
                result.insert(skip.begin(), skip.end());
            }

            int nextOpen = open;
            if (s[i] == '(') {
                ++nextOpen;
            } else if (s[i] == ')') {
                --nextOpen;
            }

            auto keep = recursive(i + 1, nextOpen);
            for (const auto& suffix : keep) {
                result.insert(s[i] + suffix);
            }

            return memo[i][open] = result;
        };

        std::unordered_set<std::string> candidates = recursive(0, 0);

        std::vector<std::string> result{};
        auto maxElement = std::max_element(candidates.begin(), candidates.end(),
            [&](const auto& l, const auto& r) {
                return l.size() < r.size();
            }
        );

        if (maxElement == candidates.end()) {
            return result;
        }

        for (const auto& c : candidates) {
            if (c.size() == maxElement->size()) {
                result.push_back(c);
            }
        }

        return result;
    }
};