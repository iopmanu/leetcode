/**
 * @author i.doronin
 */
public class MinimumReplacementsToSortTheArray {
    public long minimumReplacement(int[] nums) {
        long ops = 0;
        long limit = nums[nums.length - 1];

        for (int i = nums.length - 2; i >= 0; i--) {
            long x = nums[i];
            if (x <= limit) {
                limit = x;
            } else {
                long k = (x + limit - 1) / limit;
                ops += k - 1;
                limit = x / k;
            }
        }
        return ops;
    }
}
