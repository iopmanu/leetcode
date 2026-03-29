import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

/**
 * @author i.doronin
 */
public class LongestWordInDictionary {
    public String longestWord(String[] words) {
        String[] sorted = Arrays.stream(words).sorted().toArray(String[]::new);
        Set<String> components = new HashSet<>();
        String retval = "";

        for (String word : sorted) {
            if (word.length() == 1 || components.contains(word.substring(0, word.length() - 1))) {
                retval = word.length() > retval.length() ? word : retval;
                components.add(word);
            }
        }

        return retval;
    }
}
