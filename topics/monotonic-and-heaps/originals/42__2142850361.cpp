class Solution {
public:
    int trap(vector<int>& height) {
        std::deque<int> ms{};

        int result = 0;
        for (int i = 0; i < height.size(); i++) {
            while (!ms.empty() && height[ms.back()] < height[i]) {
                int pivot = ms.back();
                ms.pop_back();

                if (ms.empty()) {
                    break;
                }

                result += (i - ms.back() - 1) * std::min(
                    height[i] - height[pivot], 
                    height[ms.back()] - height[pivot]
                );                  
            }

            ms.push_back(i);
        }

        return result;
    }
};