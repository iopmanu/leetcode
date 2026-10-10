class Solution {
public:
    int maxTurbulenceSize(vector<int>& arr) {
        int len = 1, retval = 1;
        uint8_t prevComparsion = 0;

        for (int i = 1; i < arr.size(); i++) {
            uint8_t currentComparsion = getSign(arr[i - 1], arr[i]);

            if (currentComparsion == 3) {
                len = 1;
                prevComparsion = 0;
                continue;
            }

            bool isStillTurbulent = isTurbulent(prevComparsion, currentComparsion);

            if (isStillTurbulent) {
                len++;
            } else {
                len = 2;
            }

            retval = max(len, retval);
            prevComparsion = currentComparsion;
        }

        return retval;
    }

    uint8_t getSign(int lhs, int rhs) {
        if (lhs > rhs) {
            return 1;
        } else if (rhs > lhs) {
            return 2;
        }
        return 3;
    }

    bool isTurbulent(uint8_t prev, uint8_t current) {
        return prev == 0 || (prev == 1 && current == 2) || (prev == 2 && current == 1);
    }
};