#include <cstddef>
#include <utility>
#include <vector>

void wiggleSort(std::vector<int>& nums) {
    for (std::size_t i = 1; i < nums.size(); ++i) {
        const bool violatesWiggle =
                (i % 2 == 1 && nums[i] < nums[i - 1]) ||
                (i % 2 == 0 && nums[i] > nums[i - 1]);

        if (violatesWiggle) {
            std::swap(nums[i], nums[i - 1]);
        }
    }
}
