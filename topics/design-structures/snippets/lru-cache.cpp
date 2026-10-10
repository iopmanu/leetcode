class LRUCache {
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map{};
    std::list<std::pair<int, int>> values{};
    int capacity = 0;

public:
    LRUCache(int capacity) : capacity (capacity) {
    }
    
    int get(int key) {
        if (!map.contains(key)) {
            return -1;
        }

        auto it = map[key];
        values.splice(values.begin(), values, it);
        return it->second;
    }
    
    void put(int key, int value) {
        if (map.contains(key)) {
            values.splice(values.begin(), values, map[key]);
            values.begin()->second = value;
            map[key] = values.begin();
            return;
        }
        
        if (map.size() >= capacity) {
            auto p = values.back();
            values.pop_back();
            map.erase(p.first);
        }


        values.push_front(std::make_pair(key, value));
        map[key] = values.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */