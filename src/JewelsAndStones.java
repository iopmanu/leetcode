import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * @author i.doronin
 *
 * You're given strings jewels representing the types of stones that are jewels, and stones representing the stones
 * you have. Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.
 *
 * Letters are case sensitive, so "a" is considered a different type of stone from "A".
 */
public class JewelsAndStones {
    public int numJewelsInStones(String jewels, String stones) {
        Set<Integer> jewelsSet = jewels.chars()
                .boxed()
                .collect(Collectors.toSet());

        return stones.chars().filter(jewelsSet::contains).toArray().length;
    }
}
