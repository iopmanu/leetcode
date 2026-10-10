class Solution {
private:
public:
    int maximumCostSubstring(
        std::string s,
        std::string chars,
        std::vector<int>& vals
    ) {
        auto overrides = costsFromZip(chars, vals);

        int retval = 0;
        int current = 0;
        for (int i = 0; i < s.size(); i++) {
            auto score = getOverride(overrides, s[i])
                .value_or(getScore(s[i]));
            
            current += score;
            retval = max(retval, current);

            if (current < 0) {
                current = 0;
            }
        }

        return retval;
    }

private:

    std::optional<int> getOverride(
    const std::unordered_map<char, int>& overrides,
    char ch
    ) {
        auto it = overrides.find(ch);
        return it != overrides.end()
            ? std::optional<int>{it->second}
            : std::nullopt;
    }

    static size_t getScore(char curr) {
        return curr - static_cast<size_t>('a') + 1;
    }

    std::unordered_map<char, int> costsFromZip(
        const std::string& chars,
        const std::vector<int>& vals
    ) {
        std::unordered_map<char, int> mapping{chars.size()};

        for (int i = 0; i < chars.size(); i++) {
            mapping.emplace(chars[i], vals[i]);
        }

        return mapping;
    }
};