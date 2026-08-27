#include <unordered_map>
#include <vector>

class Solution {
public:
    int countElements(const std::vector<int>& arr) {
        std::unordered_map<int, int> counts{};

        for (const auto num : arr) {
            ++counts[num];
        }

        int result = 0;

        for (auto [k, v] : counts) {
            if (counts.contains(k + 1)) {
                result += v;
            }
        }

        return result;
    }
};
