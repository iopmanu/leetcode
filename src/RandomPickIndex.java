import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.random.RandomGenerator;
import java.util.random.RandomGeneratorFactory;

/**
 * @author i.doronin
 * <p>
 * Given an integer array nums with possible duplicates, randomly output the index of a given target number. You can assume that the given target number must exist in the array.
 * <p>
 * Implement the Solution class:
 * <p>
 * Solution(int[] nums) Initializes the object with the array nums.
 * int pick(int target) Picks a random index i from nums where nums[i] == target. If there are multiple valid i's, then each index should have an equal probability of returning.
 */
class Solution {
    private final HashMap<Integer, List<Integer>> valueToIndex = new HashMap<>();
    private final RandomGenerator generator = RandomGeneratorFactory.getDefault().create();

    public Solution(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            int value = nums[i];
            valueToIndex.computeIfAbsent(value, (v) -> new ArrayList<>()).add(i);
        }
    }

    public int pick(int target) {
        var indices = valueToIndex.get(target);
        if (indices == null) {
            return -1;
        }

        return indices.get(generator.nextInt(indices.size()));
    }
}
