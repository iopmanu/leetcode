import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Stream;

/**
 * @author i.doronin
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and is able to see the 10 most recent tweets in the user's news feed.
 * <p>
 * Implement the Twitter class:
 * <p>
 * Twitter() Initializes your twitter object.
 * void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId. Each call to this function will be made with a unique tweetId.
 * List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user themself. Tweets must be ordered from most recent to least recent.
 * void follow(int followerId, int followeeId) The user with ID followerId started following the user with ID followeeId.
 * void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the user with ID followeeId.
 */
class Twitter {
    private record TweetWithOrder(int id, int order) {
        public static TweetWithOrder of(int id, int order) {
            return new TweetWithOrder(id, order);
        }
    }

    private final HashMap<Integer, Set<Integer>> userFollows;
    private final HashMap<Integer, List<TweetWithOrder>> userTweets;

    private int order;

    public Twitter() {
        this.userFollows = new HashMap<>();
        this.userTweets = new HashMap<>();
        this.order = 0;
    }

    public void postTweet(int userId, int tweetId) {
        userTweets.computeIfAbsent(userId, k -> new ArrayList<>()).add(TweetWithOrder.of(tweetId, order++));
    }

    public List<Integer> getNewsFeed(int userId) {
        return Stream.concat(Optional.ofNullable(userFollows.get(userId)).stream().flatMap(Collection::stream), Stream.of(userId))
                .map(uid -> Optional.ofNullable(userTweets.get(uid)).orElse(List.of()))
                .flatMap(Collection::stream)
                .sorted(Comparator.comparingLong(TweetWithOrder::order).reversed())
                .map(TweetWithOrder::id)
                .distinct()
                .limit(10)
                .toList();
    }

    public void follow(int followerId, int followeeId) {
        userFollows.computeIfAbsent(followerId, v -> new HashSet<>()).add(followeeId);
    }

    public void unfollow(int followerId, int followeeId) {
        Optional.ofNullable(userFollows.get(followerId))
                .ifPresent(followees -> followees.remove(followeeId));
    }
}

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * List<Integer> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */
