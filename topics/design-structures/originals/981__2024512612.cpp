class TimeMap {
    std::unordered_map<std::string, std::map<int, std::string>> cache;
public:
    TimeMap() : cache({}) {
    }
    
    void set(string key, string value, int timestamp) {
        cache[key].insert({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto it = cache[key].upper_bound(timestamp);
        return it == cache[key].begin() ? "" : prev(it)->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */