/**
 * @author i.doronin
 */
public class MaxChunksToMakeSorted {
    public int maxChunksToSorted(int[] arr) {
        int n = arr.length;
        int[] maxLeft = new int[n];
        maxLeft[0] = arr[0];
        for (int i = 1; i < n; i++) {
            maxLeft[i] = Math.max(maxLeft[i - 1], arr[i]);
        }

        int[] minRight = new int[n];
        minRight[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = Math.min(minRight[i + 1], arr[i]);
        }

        int chunks = 0;
        for (int i = 0; i < n; i++) {
            if (maxLeft[i] <= minRight[i + 1]) {
                chunks += 1;
            }
        }

        return chunks;
    }
}

// [1,0,2,3,4]
// [0,1,2,3,4]
// [n,c,c,c,c]
