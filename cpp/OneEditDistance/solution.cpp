#include <cstddef>
#include <cstring>
#include <string>

class Solution {
public:
    bool isOneEditDistance(
            const std::string& first,
            const std::string& second
    ) {
        if (first.size() > second.size()) {
            return isOneEditDistance(second, first);
        }

        if (second.size() - first.size() > 1) {
            return false;
        }

        for (std::size_t i = 0; i < first.size(); ++i) {
            if (first[i] == second[i]) {
                continue;
            }

            if (first.size() == second.size()) {
                return !std::strcmp(first.data() + i + 1, second.data() + i + 1);
            }

            return !std::strcmp(first.data() + i, second.data() + i + 1);
        }

        return first.size() + 1 == second.size();
    }
};
