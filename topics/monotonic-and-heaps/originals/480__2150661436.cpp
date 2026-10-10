#include <vector>
#include <set>
#include <unordered_map>
#include <utility>

class Solution {
    struct MedianFinder {
        using TLeftHeap = std::multiset<std::pair<int, int>, std::greater<std::pair<int, int>>>;
        using TRightHeap = std::multiset<std::pair<int, int>, std::less<std::pair<int, int>>>;
        
        TLeftHeap leftHeap{};
        TRightHeap rightHeap{};
        
        std::unordered_map<int, TLeftHeap::iterator> leftMapping{};
        std::unordered_map<int, TRightHeap::iterator> rightMapping{};

        void push(int index, int num) {
            if (leftHeap.empty() || num <= leftHeap.begin()->first) {
                leftMapping[index] = leftHeap.insert(std::make_pair(num, index));
            } else {
                rightMapping[index] = rightHeap.insert(std::make_pair(num, index));
            }
            balance();
        }

        void remove(int idx) {
            if (leftMapping.contains(idx)) {
                leftHeap.erase(leftMapping[idx]);
                leftMapping.erase(idx);
            } else if (rightMapping.contains(idx)) {
                rightHeap.erase(rightMapping[idx]);
                rightMapping.erase(idx);
            }
            balance();
        }

        double findMedian() {
            if (size() % 2 == 0) {
                return (static_cast<double>(leftHeap.begin()->first) + rightHeap.begin()->first) / 2.0;
            }
            return static_cast<double>(leftHeap.begin()->first);
        }

        int size() const {
            return leftHeap.size() + rightHeap.size();
        }

    private:
        void balance() {
            if (leftHeap.size() > rightHeap.size() + 1) {
                auto topIt = leftHeap.begin();
                int val = topIt->first;
                int idx = topIt->second;

                leftHeap.erase(topIt);
                leftMapping.erase(idx);                
                rightMapping[idx] = rightHeap.insert(std::make_pair(val, idx));
            } 
            else if (rightHeap.size() > leftHeap.size()) {
                auto topIt = rightHeap.begin();
                int val = topIt->first;
                int idx = topIt->second;

                rightHeap.erase(topIt);
                rightMapping.erase(idx);
                leftMapping[idx] = leftHeap.insert(std::make_pair(val, idx));
            }
        }
    };

public:
    std::vector<double> medianSlidingWindow(std::vector<int>& nums, int k) {
        MedianFinder finder{};
        std::vector<double> result{};
        
        for (int i = 0; i < nums.size(); ++i) {
            finder.push(i, nums[i]);

            if (finder.size() > k) {
                finder.remove(i - k);
            }

            if (finder.size() == k) {
                result.push_back(finder.findMedian());
            }
        }

        return result;
    }
};
