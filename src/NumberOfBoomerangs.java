import java.util.HashMap;

/**
 * @author i.doronin
 * <p>
 * You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple
 * of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).
 *
 * Return the number of boomerangs.
 */
class Solution {
    public int numberOfBoomerangs(int[][] points) {
        int result = 0;

        for (int[] x : points) {
            HashMap<Integer, Integer> distanceCounts = new HashMap<>();

            for (int[] y : points) {
                Integer key = squared(x[0] - y[0]) + squared(x[1] - y[1]);
                distanceCounts.put(key, distanceCounts.getOrDefault(key, 0) + 1);
            }

            for (var entry : distanceCounts.entrySet()) {
                var count = entry.getValue();
                if (count >= 2) {
                    result += count * (count - 1);
                }
            }
        }


        return result;
    }

    private static int squared(int a) {
        return a * a;
    }
}