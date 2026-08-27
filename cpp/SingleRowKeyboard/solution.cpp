#include <cstdlib>
#include <string>
#include <unordered_map>

class Solution {
public:
    int calculateTime(
            const std::string& keyboard,
            const std::string& word
    ) {
        std::unordered_map<char, int> positions{};

        for (int i = 0; i < keyboard.size(); ++i) {
            positions[keyboard[i]] = i;
        }

        int result = 0;
        int position = 0;

        for (char ch : word) {
            int nextPosition = positions[ch];
            result += std::abs(nextPosition - position);
            position = nextPosition;
        }

        return result;
    }
};
