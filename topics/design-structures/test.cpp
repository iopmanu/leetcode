#include "templates.hpp"
#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

using namespace patterns::design;

// Deliberately slow timestamp model, independent of list/set implementations.
struct CacheModel {
    struct Entry { int value; int frequency; int time; };
    std::map<int, Entry> entries;
    int capacity;
    bool lfu;
    int timer = 0;
    CacheModel(int limit, bool useFrequency) : capacity(limit), lfu(useFrequency) {}
    std::optional<int> get(int key) {
        if (!entries.contains(key)) return std::nullopt;
        auto& entry = entries[key];
        ++entry.frequency;
        entry.time = ++timer;
        return entry.value;
    }
    void put(int key, int value) {
        if (capacity <= 0) return;
        if (entries.contains(key)) {
            get(key);
            entries[key].value = value;
            return;
        }
        if (static_cast<int>(entries.size()) == capacity) {
            auto victim = entries.begin();
            for (auto it = entries.begin(); it != entries.end(); ++it) {
                auto rank = [&](const Entry& item) { return std::make_pair(lfu ? item.frequency : 0, item.time); };
                if (rank(it->second) < rank(victim->second)) victim = it;
            }
            entries.erase(victim);
        }
        entries[key] = {value, 1, ++timer};
    }
};

template <class Cache>
void checkCache(bool lfu, std::mt19937& random) {
    for (int capacity = -1; capacity <= 8; ++capacity) {
        Cache cache(capacity);
        CacheModel model(capacity, lfu);
        for (int step = 0; step < 3000; ++step) {
            int key = static_cast<int>(random() % 15) - 7;
            if (random() % 2) {
                int value = static_cast<int>(random() % 21) - 10;
                cache.put(key, value);
                model.put(key, value);
            } else assert(cache.get(key) == model.get(key));
        }
    }
}

int main() {
    static_assert(!std::is_copy_constructible_v<LRUCache>);
    static_assert(!std::is_move_constructible_v<LRUCache>);
    static_assert(!std::is_copy_constructible_v<LFUCache>);
    static_assert(!std::is_copy_constructible_v<LFUCacheOrdered>);
    LRUCache lru(2);
    lru.put(1, -1); lru.put(2, 2);
    assert(lru.get(1) == -1);
    lru.put(3, 3);
    assert(!lru.get(2));
    lru.put(1, 10);
    assert(lru.get(1) == 10);
    LFUCache lfu(2);
    lfu.put(1, 1); lfu.put(2, 2);
    assert(lfu.get(1) == 1);
    lfu.put(3, 3);
    assert(!lfu.get(2));
    assert(lfu.get(3) == 3);
    lfu.put(4, 4);
    assert(!lfu.get(1));
    std::mt19937 random(146460706);
    checkCache<LRUCache>(false, random);
    checkCache<LFUCache>(true, random);
    checkCache<LFUCacheOrdered>(true, random);
    MyHashMap hash;
    std::unordered_map<int, int> reference;
    for (int key : {INT_MIN, INT_MAX, -32, -1, 0, 32, 64}) {
        hash.put(key, -1);
        assert(hash.get(key) == -1);
        hash.put(key, key);
        assert(hash.get(key) == key);
        hash.remove(key);
        assert(!hash.get(key));
    }
    for (int step = 0; step < 10000; ++step) {
        int key = (static_cast<int>(random() % 100) - 50) * 32;
        int action = static_cast<int>(random() % 3);
        if (action == 0) {
            int value = static_cast<int>(random());
            hash.put(key, value); reference[key] = value;
        } else if (action == 1) {
            hash.remove(key); reference.erase(key);
        } else {
            std::optional<int> expected;
            if (reference.contains(key)) expected = reference[key];
            assert(hash.get(key) == expected);
        }
    }
    FreqStack example;
    for (int value : {5, 7, 5, 7, 4, 5}) example.push(value);
    for (int expected : {5, 7, 5, 4, 7, 5}) assert(example.pop() == expected);
    example.push(-1);
    assert(example.pop() == -1);
    FreqStack stack;
    bool threw = false;
    try { stack.pop(); } catch (const std::out_of_range&) { threw = true; }
    assert(threw);
    std::vector<int> history;
    for (int step = 0; step < 10000; ++step) {
        if (history.empty() || random() % 3) {
            int value = static_cast<int>(random() % 20) - 10;
            stack.push(value); history.push_back(value);
        } else {
            std::map<int, int> counts;
            int best = 0;
            for (int value : history) best = std::max(best, ++counts[value]);
            int victim = static_cast<int>(history.size()) - 1;
            while (counts[history[victim]] != best) --victim;
            assert(stack.pop() == history[victim]);
            history.erase(history.begin() + victim);
        }
    }
    Twitter twitter;
    assert(twitter.getNewsFeed(7).empty());
    twitter.postTweet(1, 11);
    twitter.follow(1, 1);
    assert(twitter.getNewsFeed(1) == std::vector<int>{11});
    assert(twitter.getNewsFeed(1, 0).empty());
    twitter.unfollow(1, 1);
    std::map<int, std::set<int>> following;
    std::vector<std::pair<int, int>> posts{{1, 11}};
    for (int step = 0; step < 3000; ++step) {
        int user = static_cast<int>(random() % 10);
        int other = static_cast<int>(random() % 10);
        int action = static_cast<int>(random() % 4);
        if (action == 0) {
            int tweet = step + 100;
            twitter.postTweet(user, tweet); posts.push_back({user, tweet});
        } else if (action == 1) {
            twitter.follow(user, other);
            if (user != other) following[user].insert(other);
        } else if (action == 2) {
            twitter.unfollow(user, other); following[user].erase(other);
        } else {
            std::size_t limit = random() % 15;
            std::vector<int> expected;
            for (auto it = posts.rbegin(); it != posts.rend() && expected.size() < limit; ++it) {
                if (it->first == user || following[user].contains(it->first)) expected.push_back(it->second);
            }
            assert(twitter.getNewsFeed(user, limit) == expected);
        }
    }
    std::cout << "design-structures: 90,000 cache operations + 23,000 other seeded operations passed\n";
}
