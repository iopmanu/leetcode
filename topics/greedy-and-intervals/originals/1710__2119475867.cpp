class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        std::sort(
            boxTypes.begin(),
            boxTypes.end(),
            [](const auto& a, const auto& b) {
                return a[1] < b[1];
            }
        );

        int units = 0;
        for (int i = boxTypes.size() - 1; i >= 0 && truckSize > 0; --i) {
            units += min(truckSize, boxTypes[i][0]) * boxTypes[i][1];
            truckSize -= boxTypes[i][0];
        }

        return units;
    }
};