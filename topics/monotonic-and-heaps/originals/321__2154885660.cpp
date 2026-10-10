class Solution {
public:
    std::vector<int> select(const std::vector<int>& nums, int length) {
        int canDrop = nums.size() - length;
        std::deque<int> ms{};
        for (int i = 0; i < nums.size(); i++) {
            while (!ms.empty() && canDrop > 0 && ms.back() < nums[i]) {
                ms.pop_back();
                canDrop--;
            }

            ms.push_back(nums[i]);
        }

        std::vector<int> result{};
        while (!ms.empty()) {
            result.push_back(ms.front());
            ms.pop_front();
        }

        result.resize(length);
        return result;
    }

    std::vector<int> merge(std::vector<int>& l, std::vector<int>& r) {
        std::vector<int> result(l.size() + r.size(), 0);
        int accumulator = 0;

        int lPtr = 0; int rPtr = 0;
        std::span<int> fullL{l}; std::span<int> fullR{r};
        for (int i = 0; i < result.size(); i++) {
            if (lPtr == l.size()) {
                result[i] = r[rPtr++];
                continue;
            }

            if (rPtr == r.size()) {
                result[i] = l[lPtr++];
                continue;
            }

            std::span<int> lspan = fullL.subspan(lPtr);
            std::span<int> rspan = fullR.subspan(rPtr);
            
            auto compare = std::lexicographical_compare_three_way(
                lspan.begin(), lspan.end(),
                rspan.begin(), rspan.end()
            );

            if (std::is_gt(compare)) {
                result[i] = lspan[0];
                lPtr++;
            } else {
                result[i] = rspan[0];
                rPtr++;
            }
        }

        return result;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        if (nums1.size() > nums2.size()) {
            return maxNumber(nums2, nums1, k);
        }

        int start_k1 = std::max(0, k - (int)nums2.size());
        int end_k1 = std::min(k, (int)nums1.size());

        std::vector<int> bestResult = {};
        for (int k1 = start_k1; k1 <= end_k1; k1++) {
            int k2 = k - k1;

            std::vector<int> left = select(nums1, k1);
            std::vector<int> right = select(nums2, k2);

            auto merged = merge(left, right);
            if (merged > bestResult) {
                bestResult = std::move(merged);
            }
        }

        return bestResult;
    }
};