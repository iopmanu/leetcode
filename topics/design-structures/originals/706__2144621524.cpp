class MyHashMap {
    std::vector<std::list<std::pair<int, int>>> storage{};
public:
    MyHashMap() : storage(32) {
        
    }
    
    void put(int key, int value) {
        auto& bucket = storage[key % storage.size()];
        for (auto it = bucket.begin(), end = bucket.end(); it != end; ++it) {
            if (it->first == key) {
                it->second = value;
                return;
            }
        }

        bucket.push_back(std::make_pair(key, value));
    }
    
    int get(int key) {
        auto& bucket = storage[key % storage.size()];
        for (auto it = bucket.begin(), end = bucket.end(); it != end; ++it) {
            if (it->first == key) {
                return it->second;
            }
        }

        return -1;
    }
    
    void remove(int key) {
        auto& bucket = storage[key % storage.size()];
        for (auto it = bucket.begin(), end = bucket.end(); it != end; ++it) {
            if (it->first == key) {
                bucket.erase(it);
                return;
            }
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */