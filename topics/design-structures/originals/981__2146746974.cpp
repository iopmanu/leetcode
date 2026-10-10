class TimeMap {
    std::unordered_map<std::string, std::map<int, std::string>> storage{};

public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        storage[key][timestamp] = value;
    }
    
    string get(string key, int timestamp) {
        auto it = storage[key].upper_bound(timestamp);
        return it == storage[key].begin() ? "" : std::prev(it)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */