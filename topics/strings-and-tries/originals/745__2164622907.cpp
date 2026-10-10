class WordFilter {
    struct Node {
        std::unordered_map<char, std::unique_ptr<Node>> nodes{};
        int index = -1;
    };

    struct Trie {
        Node root{};

        void insert(const std::string& s, int idx) {
            Node* current = &root;
            for (char ch : s) {
                auto it = current->nodes.find(ch);
                if (it == current->nodes.end()) {
                    current->nodes[ch] = std::make_unique<Node>();
                }

                current = current->nodes[ch].get();
                current->index = idx;
            }
        }

        Node* getLeaf(const std::string& s) {
            Node* current = &root;
            for (char ch : s) {
                auto it = current->nodes.find(ch);
                if (it == current->nodes.end()) {
                    return nullptr;
                }
                current = current->nodes[ch].get();
            }
            return current;
        }

        int search(const std::string& s) {
            auto node = getLeaf(s);
            return node != nullptr ? node->index : -1;
        }
    };
    

    Trie trie{};
public:
    WordFilter(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j <= words[i].size(); j++) {
                trie.insert(words[i].substr(j) + "{" + words[i], i);
            }
        }
    }
    
    int f(string pref, string suff) {
        return trie.search(suff + "{" + pref);
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */