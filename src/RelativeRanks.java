import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

/**
 * @author i.doronin
 */
public class RelativeRanks {
    private record RankWithIndex(int index, int rank) {}

    public String[] findRelativeRanks(int[] score) {
        List<RankWithIndex> ranks = new ArrayList<>(score.length);
        for (int i = 0; i< score.length; i++) {
            ranks.add(new RankWithIndex(i, score[i]));
        }
        ranks.sort(Comparator.comparingInt(RankWithIndex::rank).reversed());

        String[] result = new String[ranks.size()];
        for (int i = 0; i < ranks.size(); i++) {
            result[ranks.get(i).index] = convertRank(i + 1);
        }

        return result;
    }

    private static String convertRank(int rank) {
        return switch(rank) {
            case 1 -> "Gold Medal";
            case 2 -> "Silver Medal";
            case 3 -> "Bronze Medal";
            default -> String.valueOf(rank);
        };
    }
}
