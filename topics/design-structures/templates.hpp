#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <limits>
#include <list>
#include <optional>
#include <queue>
#include <set>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace patterns::design {

// Optional lookups distinguish missing keys from stored -1.
// Iterator-owning classes deliberately forbid copying and moving.
class LRUCache {
    using List = std::list<std::pair<int, int>>;
    List values;
    std::unordered_map<int, List::iterator> mapping;
    std::size_t capacity;
public:
    explicit LRUCache(int limit) : capacity(static_cast<std::size_t>(std::max(0, limit))) {}
    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache(LRUCache&&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;

    std::optional<int> get(int key) {
        auto it = mapping.find(key);
        if (it == mapping.end()) return std::nullopt;
        values.splice(values.begin(), values, it->second);
        return it->second->second;
    }
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = mapping.find(key);
        if (it != mapping.end()) {
            it->second->second = value;
            values.splice(values.begin(), values, it->second);
            return;
        }
        if (mapping.size() == capacity) {
            mapping.erase(values.back().first);
            values.pop_back();
        }
        values.push_front(std::make_pair(key, value));
        mapping[key] = values.begin();
    }
};

class LFUCache {
    struct Node { int key; int value; std::uint64_t frequency; };
    using List = std::list<Node>;
    std::unordered_map<std::uint64_t, List> storage;
    std::unordered_map<int, List::iterator> mapping;
    std::size_t capacity;
    std::uint64_t minFreq = 0;

    void update(List::iterator it) {
        Node node = *it;
        if (node.frequency == std::numeric_limits<std::uint64_t>::max()) {
            throw std::overflow_error("cache frequency exhausted");
        }
        auto old = storage.find(node.frequency);
        old->second.erase(it);
        if (old->second.empty()) {
            if (node.frequency == minFreq) ++minFreq;
            storage.erase(old);
        }
        ++node.frequency;
        auto& bucket = storage[node.frequency];
        bucket.push_front(node);
        mapping[node.key] = bucket.begin();
    }
public:
    explicit LFUCache(int limit) : capacity(static_cast<std::size_t>(std::max(0, limit))) {}
    LFUCache(const LFUCache&) = delete;
    LFUCache& operator=(const LFUCache&) = delete;
    LFUCache(LFUCache&&) = delete;
    LFUCache& operator=(LFUCache&&) = delete;

    std::optional<int> get(int key) {
        auto it = mapping.find(key);
        if (it == mapping.end()) return std::nullopt;
        int value = it->second->value;
        update(it->second);
        return value;
    }
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = mapping.find(key);
        if (it != mapping.end()) {
            update(it->second);
            mapping.at(key)->value = value;
            return;
        }
        if (mapping.size() == capacity) {
            auto victim = storage.find(minFreq);
            mapping.erase(victim->second.back().key);
            victim->second.pop_back();
            if (victim->second.empty()) storage.erase(victim);
        }
        minFreq = 1;
        auto& bucket = storage[minFreq];
        bucket.push_front({key, value, 1});
        mapping[key] = bucket.begin();
    }
};

// Older #460 strategy: total ordering makes the eviction policy explicit.
class LFUCacheOrdered {
    using Node = std::tuple<std::uint64_t, std::uint64_t, int, int>;
    using Set = std::set<Node>;
    Set frequencies;
    std::unordered_map<int, Set::iterator> storage;
    std::size_t capacity;
    std::uint64_t globalTime = 0;

    std::uint64_t nextTime() {
        if (globalTime == std::numeric_limits<std::uint64_t>::max()) {
            throw std::overflow_error("cache timestamp exhausted");
        }
        return globalTime++;
    }
    void update(Set::iterator it, int value) {
        auto [frequency, time, key, oldValue] = *it;
        (void)time;
        (void)oldValue;
        if (frequency == std::numeric_limits<std::uint64_t>::max()) {
            throw std::overflow_error("cache frequency exhausted");
        }
        std::uint64_t now = nextTime();
        frequencies.erase(it);
        storage[key] = frequencies.insert({frequency + 1, now, key, value}).first;
    }
public:
    explicit LFUCacheOrdered(int limit) : capacity(static_cast<std::size_t>(std::max(0, limit))) {}
    LFUCacheOrdered(const LFUCacheOrdered&) = delete;
    LFUCacheOrdered& operator=(const LFUCacheOrdered&) = delete;
    LFUCacheOrdered(LFUCacheOrdered&&) = delete;
    LFUCacheOrdered& operator=(LFUCacheOrdered&&) = delete;

    std::optional<int> get(int key) {
        auto it = storage.find(key);
        if (it == storage.end()) return std::nullopt;
        int value = std::get<3>(*it->second);
        update(it->second, value);
        return value;
    }
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = storage.find(key);
        if (it != storage.end()) { update(it->second, value); return; }
        std::uint64_t now = nextTime();
        if (storage.size() == capacity) {
            auto victim = frequencies.begin();
            storage.erase(std::get<2>(*victim));
            frequencies.erase(victim);
        }
        storage[key] = frequencies.insert({1, now, key, value}).first;
    }
};

// Fixed 32 chains, intentionally no resizing. O(chain length) per operation.
class MyHashMap {
    std::array<std::list<std::pair<int, int>>, 32> storage;
    static std::size_t bucketIndex(int key) {
        int index = key % 32;
        if (index < 0) index += 32;
        return static_cast<std::size_t>(index);
    }
public:
    void put(int key, int value) {
        auto& bucket = storage[bucketIndex(key)];
        for (auto& item : bucket) {
            if (item.first == key) { item.second = value; return; }
        }
        bucket.push_back(std::make_pair(key, value));
    }
    std::optional<int> get(int key) const {
        const auto& bucket = storage[bucketIndex(key)];
        for (const auto& item : bucket) if (item.first == key) return item.second;
        return std::nullopt;
    }
    void remove(int key) {
        auto& bucket = storage[bucketIndex(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) { bucket.erase(it); return; }
        }
    }
};

class FreqStack {
    std::unordered_map<int, std::size_t> route;
    std::unordered_map<std::size_t, std::vector<int>> freqs;
    std::size_t maxFreq = 0;
public:
    void push(int value) {
        std::size_t frequency = ++route[value];
        freqs[frequency].push_back(value);
        maxFreq = std::max(maxFreq, frequency);
    }
    int pop() {
        if (maxFreq == 0) throw std::out_of_range("pop from an empty frequency stack");
        auto& bucket = freqs.at(maxFreq);
        int value = bucket.back();
        bucket.pop_back();
        if (--route[value] == 0) route.erase(value);
        if (bucket.empty()) { freqs.erase(maxFreq); --maxFreq; }
        return value;
    }
};

// Scan relevant history into a bounded min-heap: source algorithm, not k-way merge.
class Twitter {
    using Post = std::pair<std::uint64_t, int>;
    std::unordered_map<int, std::unordered_set<int>> following;
    std::unordered_map<int, std::vector<Post>> tweets;
    std::uint64_t timestamp = 0;
public:
    void postTweet(int userId, int tweetId) {
        if (timestamp == std::numeric_limits<std::uint64_t>::max()) {
            throw std::overflow_error("post timestamp exhausted");
        }
        tweets[userId].push_back(std::make_pair(timestamp++, tweetId));
    }
    std::vector<int> getNewsFeed(int userId, std::size_t limit = 10) const {
        if (limit == 0) return {};
        std::priority_queue<Post, std::vector<Post>, std::greater<Post>> heap;
        auto scan = [&](int author) {
            auto it = tweets.find(author);
            if (it == tweets.end()) return;
            for (const auto& post : it->second) {
                heap.push(post);
                if (heap.size() > limit) heap.pop();
            }
        };
        auto it = following.find(userId);
        if (it != following.end()) for (int author : it->second) scan(author);
        scan(userId);
        std::vector<int> result;
        while (!heap.empty()) { result.push_back(heap.top().second); heap.pop(); }
        std::reverse(result.begin(), result.end());
        return result;
    }
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) following[followerId].insert(followeeId);
    }
    void unfollow(int followerId, int followeeId) {
        auto it = following.find(followerId);
        if (it != following.end()) it->second.erase(followeeId);
    }
};

}  // namespace patterns::design
