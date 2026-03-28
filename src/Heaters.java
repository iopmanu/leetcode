import java.util.Arrays;

/**
 * @author i.doronin
 */
public class Heaters {
    public int findRadius(int[] houses, int[] heaters) {
        houses = Arrays.stream(houses).sorted().toArray();
        heaters = Arrays.stream(heaters).sorted().toArray();

        if (heaters.length == 0) {
            return -1;
        }

        if (houses.length == 0) {
            return 0;
        }

        int radius = 0;
        for (int house : houses) {
            radius = Math.max(calcRadius(heaters, house), radius);
        }

        return radius;
    }

    private int calcRadius(int[] heaters, int house) {
        int left = 0;
        int right = heaters.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (heaters[mid] == house) {
                return 0;
            } else if (heaters[mid] < house) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return Math.min(
                Math.abs(house - heaters[left]),
                left > 0 ? Math.abs(house - heaters[left - 1]) : Integer.MAX_VALUE
        );
    }
}
