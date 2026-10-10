class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using TStorage = std::vector<int>;
        std::priority_queue<TStorage, std::vector<TStorage>, std::greater<>> pq{};

        int max = INT_MIN;
        for (int i = 0 ; i < nums.size(); i++) {
            pq.push({nums[i][0], i, 0});
            max = std::max(nums[i][0], max);
        }

        std::vector<int> range{0, INT_MAX};
        while (true) {
            auto min = pq.top()[0];
            auto row = pq.top()[1];
            auto col = pq.top()[2];
            pq.pop();

            if (max - min < range[1] - range[0]) {
                range[0] = min;
                range[1] = max;
            }

            if (++col == nums[row].size()) {
                break;
            }

            pq.push({nums[row][col], row, col});
            max = std::max(nums[row][col], max);
        }

        return range;
    }
};