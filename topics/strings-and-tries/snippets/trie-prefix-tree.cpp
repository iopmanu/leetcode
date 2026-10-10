class Trie {
    struct Node {
        std::unordered_map<char, Node> level{};
        bool leaf = false;
    };

    Node root;
public:
    Trie() : root(Node{}) {
    }
    
    void insert(string s) {
        Node* current = &root;
        for (char ch : s) {
            if (!current->level.contains(ch)) {
                current->level[ch] = Node{};
            }
            
            current = &current->level[ch];
        }

        current->leaf = true;
    }
    
    bool search(string word) {
        Node* current = &root;
        for (char ch : word) {
            if (!current->level.contains(ch)) {
                return false;
            }

            current = &current->level[ch];
        }

        return current->leaf;
    }
    
    bool startsWith(string prefix) {
        Node* current = &root;
        for (char ch : prefix) {
            if (!current->level.contains(ch)) {
                return false;
            }

            current = &current->level[ch];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */