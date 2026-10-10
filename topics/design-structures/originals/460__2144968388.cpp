#include <unordered_map>
#include <list>
#include <vector>
#include <iterator>

class LFUCache {
    struct Node {
        int key;
        int value;
        int freq;
    };

    std::unordered_map<int, std::list<Node>> storage{};
    std::unordered_map<int, std::list<Node>::iterator> mapping{};
    
    int capacity;
    int minFreq = 0;

    void update(int key, std::list<Node>::iterator it) {
        Node node = *it;
        int oldFreq = node.freq;
        
        storage[oldFreq].erase(it);
        
        if (oldFreq == minFreq && storage[oldFreq].empty()) {
            ++minFreq;
        }

        node.freq++;
        storage[node.freq].push_front(node);
        
        mapping[key] = storage[node.freq].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        auto it = mapping.find(key);
        if (it == mapping.end()) {
            return -1;
        }

        update(key, it->second);
        return it->second->value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;

        auto it = mapping.find(key);
        if (it != mapping.end()) {
            it->second->value = value;
            update(key, it->second);
            return;
        }

        if (mapping.size() >= capacity) {
            auto& freqList = storage[minFreq];
            int keyToRemove = freqList.back().key;
            
            freqList.pop_back();
            mapping.erase(keyToRemove);
        }

        minFreq = 1;
        storage[minFreq].push_front({key, value, 1});
        mapping[key] = storage[minFreq].begin();
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */