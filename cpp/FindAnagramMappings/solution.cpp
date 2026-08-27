#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> anagramMappings(
            const std::vector<int>& nums1,
            const std::vector<int>& nums2
    ) {
        std::unordered_map<int, std::vector<int>> indices{};

        for (int i = 0; i < nums2.size(); ++i) {
            indices[nums2[i]].push_back(i);
        }

        std::vector<int> result;
        result.reserve(nums1.size());

        for (int num : nums1) {
            result.push_back(indices[num].back());
            indices[num].pop_back();
        }

        return result;
    }
};
