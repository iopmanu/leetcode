import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;

/**
 * @author i.doronin
 */
public class ArrayOfDoubledPairs {
    public boolean canReorderDoubled(int[] arr) {
        int n = arr.length;
        HashMap<Integer, Integer> usages = new HashMap<>(n);
        for (int j : arr) {
            usages.put(j, usages.getOrDefault(j, 0) + 1);
        }

        List<Integer> sorted = new ArrayList<>(usages.keySet());
        sorted.sort(Comparator.comparingInt(Math::abs));

        for (var v : sorted) {
            int itself = usages.getOrDefault(v, 0);
            if (itself == 0) {
                continue;
            }

            int target = v * 2;
            int counts = usages.getOrDefault(target, 0);
            if (itself > counts) {
                return false;
            }

            usages.put(target, counts - itself);
        }

        return true;
    }
}
