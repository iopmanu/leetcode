import java.util.Arrays;

/**
 * @author i.doronin
 */
public class ValidTriangleNumber {
    public int triangleNumber(int[] nums) {
        int[] sorted = Arrays.stream(nums).sorted().toArray();
        if (sorted.length < 3) {
            return 0;
        }

        int count = 0;
        for (int k = sorted.length - 1; k >= 2; k--) {
            int i = 0; int j = k - 1;

            int c = sorted[k];
            while (i < j) {
                int a = sorted[i]; int b = sorted[j];

                if (a + b > c) {
                    count += j - i;
                    j--;
                } else {
                    i++;
                }
            }
        }

        return count;
    }
}
