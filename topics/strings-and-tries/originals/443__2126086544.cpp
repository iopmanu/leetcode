class Solution {
public:
    int compress(vector<char>& chars) {
        std::vector<char> result;
        char* curr = nullptr;
        
        int currentLength = 1;
        for (int i = 0; i < chars.size(); ++i) {
            if (curr == nullptr) {
                curr = &chars[i];
                continue;
            }

            if (chars[i] == *curr) {
                ++currentLength;
                // continue;
            } else {

                result.push_back(*curr);
                if (currentLength > 1) {
                    for (const auto num : std::to_string(currentLength)) {
                        result.push_back(num);
                    }
                }

                curr = &chars[i];
                currentLength = 1;

            }
        }

        if (curr != nullptr) {
            result.push_back(*curr);
            if (currentLength > 1) {
                for (const auto num : std::to_string(currentLength)) {
                    result.push_back(num);
                }
            }
        }

        chars = std::move(result);
        return chars.size();
    }
};