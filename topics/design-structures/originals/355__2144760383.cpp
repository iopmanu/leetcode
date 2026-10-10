class Twitter {
    int timestamp = 0;
    std::unordered_map<int, std::unordered_set<int>> following;
    std::unordered_map<int, std::vector<std::vector<int>>> tweets;

public:
    Twitter() {
    }
    
    void postTweet(int userId, int tweetId) {
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        using V = std::vector<int>;
        std::priority_queue<V, std::vector<V>, std::greater<V>> pq{};
        for (auto&& followee : following[userId]) {
            for (auto&& post : tweets[followee]) {
                pq.push(post);
                if (pq.size() > 10) {
                    pq.pop();
                }
            }
        }

        for (auto&& post : tweets[userId]) {
            pq.push(post);
            if (pq.size() > 10) {
                pq.pop();
            }
        }

        std::vector<int> result{};
        result.reserve(10);
        while (!pq.empty()) {
            result.push_back(pq.top()[1]);
            pq.pop();
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
    
    void follow(int followerId, int followeeId) {
        following[followerId].insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */