class Solution {
public:
    int compress(vector<char>& chars) {
        std::vector<char> result{};

        char* curr = nullptr;
        int currentLength = 0;
        for (int i = 0; i < chars.size(); ++i) {
            if (curr == nullptr) {
                result.push_back(chars[i]);
                curr = &chars[i];
            }

            if (chars[i] == *curr) {
                currentLength++;
            } else {
                if (currentLength > 1) {
                    std::string stringified = std::to_string(currentLength);
                    for (auto i : stringified) {
                        result.push_back(i);
                    }
                }

                curr = &chars[i];
                result.push_back(chars[i]);
                currentLength = 1;
            }
        }

        if (currentLength > 1) {
            std::string stringified = std::to_string(currentLength);
            for (auto i : stringified) {
                result.push_back(i);
            }
        }

        chars = std::move(result);
        return chars.size();
    }
};