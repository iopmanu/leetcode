#include <vector>

class Solution {
public:
    void reverseWords(std::vector<char>& chars) {
        const int size = static_cast<int>(chars.size());

        for (int i = 0; i < size / 2; ++i) {
            const char tmp = chars[size - i - 1];
            chars[size - i - 1] = chars[i];
            chars[i] = tmp;
        }

        int beginning = 0;
        for (int pivot = 0; pivot <= size; ++pivot) {
            if (pivot != size && chars[pivot] != ' ') {
                continue;
            }

            int end = pivot - 1;

            while (beginning < end) {
                const char tmp = chars[beginning];
                chars[beginning++] = chars[end];
                chars[end--] = tmp;
            }

            beginning = pivot + 1;
        }
    }
};
