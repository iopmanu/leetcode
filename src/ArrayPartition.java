import java.util.Arrays;

/**
 * @author i.doronin
 */
public class ArrayPartition {
    public int arrayPairSum(int[] nums) {
        int sum = 0;
        int[] sorted = Arrays.stream(nums).sorted().toArray();
        for (int i = 0; i < sorted.length; i += 2) {
            sum += Math.min(sorted[i], sorted[i + 1]);
        }

        return sum;
    }
}
