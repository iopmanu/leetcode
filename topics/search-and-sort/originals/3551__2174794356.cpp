class Solution {
public:
    int minSwaps(vector<int>& nums) {
        std::vector<std::vector<int>> sorted{};
        for (int i = 0; i < nums.size(); i++) {
            sorted.push_back({nums[i], i});
        }

        std::unordered_map<int, int> numberToSum{};
        for (auto num : nums) {
            if (numberToSum.contains(num)) {
                continue;
            }

            int result = 0;
            int copy = num;
            while (copy > 0) {
                result += copy % 10;
                copy /= 10;
            }

            numberToSum[num] = result;
        }

        std::sort(sorted.begin(), sorted.end(), [&](auto& l, auto& r) {
            if (numberToSum[l[0]] != numberToSum[r[0]]) {
                return numberToSum[l[0]] < numberToSum[r[0]];
            }

            return l[0] < r[0];
        });

        int result = 0;
        std::vector<bool> visited(sorted.size(), false);
        for (int i = 0; i < sorted.size(); i++) {
            if (visited[i] || sorted[i][1] == i) {
                continue;
            }

            int cycle = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = sorted[j][1]; 
                cycle++;
            }

            if (cycle > 1) {
                result += (cycle - 1);
            }
        }

        return result;
    }
};