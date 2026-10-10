class Solution {
public:
    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int result = std::min(
            getRotations(tops, bottoms, tops[0]),
            getRotations(tops, bottoms, bottoms[0])
        );

        return result == INT_MAX ? -1 : result;
    }

    int getRotations(std::vector<int>& tops, std::vector<int>& bottoms, int target) {
        int topRotation = 0;
        int bottomRotation = 0;

        for (int i = 0; i < tops.size(); i++) {
            if (tops[i] != target && bottoms[i] != target) {
                return INT_MAX;
            }

            if (tops[i] == target && bottoms[i] == target) {
                continue;
            }

            topRotation += (tops[i] == target);
            bottomRotation += (bottoms[i] == target);
        }

        return std::min(topRotation, bottomRotation);
    }
};