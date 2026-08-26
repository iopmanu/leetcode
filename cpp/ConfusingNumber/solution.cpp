class Solution {
public:
    bool confusingNumber(int n) {
        static constexpr int rotation[] = {
            0, 1, -1, -1, -1, -1, 9, -1, 8, 6
        };

        const int original = n;
        int rotated = 0;

        while (n != 0) {
            const int digit = n % 10;
            if (rotation[digit] == -1) {
                return false;
            }

            rotated = rotated * 10 + rotation[digit];
            n /= 10;
        }

        return rotated != original;
    }
};
