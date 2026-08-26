#include <cstddef>
#include <sstream>
#include <string>

class Solution {
public:
    std::string mergeAlternately(
            const std::string& first,
            const std::string& second,
            bool reversed = false
    ) {
        if (first.size() > second.size()) {
            return mergeAlternately(second, first, true);
        }

        std::ostringstream result;
        std::size_t i = 0;

        for (; i < first.size(); ++i) {
            if (reversed) {
                result << second[i] << first[i];
            } else {
                result << first[i] << second[i];
            }
        }

        for (; i < second.size(); ++i) {
            result << second[i];
        }

        return result.str();
    }
};
