class LFUCache {
    std::set<std::vector<int>> frequencies{};
    std::unordered_map<int, std::set<std::vector<int>>::iterator> storage{};
    int capacity = 0;
    int globalTime = 0;

public:
    LFUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        auto it = storage.find(key);
        if (it == storage.end()) {
            return -1;
        }

        int newFreq = (*it->second)[0] + 1;
        int value = (*it->second)[3];
        frequencies.erase(it->second);
        auto newIt = frequencies.insert({newFreq, globalTime++, key, value});
        storage[key] = newIt.first;

        return value;
    }
    
    void put(int key, int value) {
        if (capacity <= 0) {
            return;
        }

        auto it = storage.find(key);
        if (it != storage.end()) {
            int newFreq = (*it->second)[0] + 1;
            frequencies.erase(it->second);
            auto newIt = frequencies.insert({newFreq, globalTime++, key, value});
            storage[key] = newIt.first;
            return;
        }

        evict();

        auto newIt = frequencies.insert({1, globalTime++, key, value});
        storage[key] = newIt.first;
    }

    void evict() {
        if (storage.size() < capacity || frequencies.empty()) {
            return;
        }

        auto toEvict = frequencies.begin();
        storage.erase((*toEvict)[2]);
        frequencies.erase(toEvict);
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */