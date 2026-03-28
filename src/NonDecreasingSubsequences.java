import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * @author i.doronin
 * Given an integer array nums, return all the different possible non-decreasing subsequences of the given array
 * with at least two elements. You may return the answer in any order.
 */
class NonDecreasingSubsequences {
    public List<List<Integer>> findSubsequences(int[] nums) {
        Set<List<Integer>> retval = new HashSet<>();
        List<Integer> subsequence = new ArrayList<>();
        traverse(retval, subsequence, nums, 0);

        return new ArrayList<>(retval);
    }

    public void traverse(Set<List<Integer>> retval, List<Integer> subsequence, int[] nums, int index) {
        if (subsequence.size() >= 2) {
            retval.add(new ArrayList<>(subsequence));
        }

        for (int i = index; i < nums.length; i++) {
            if (subsequence.isEmpty() || subsequence.getLast() <= nums[i]) {
                subsequence.add(nums[i]);
                traverse(retval, subsequence, nums, i + 1);
                subsequence.removeLast();
            }
        }
    }
}
