/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        std::unordered_map<Node*, Node*> oldToNew{};

        std::function<Node*(Node*)> dfs = [&](Node* current) {
            if (!current) {
                return (Node*) nullptr;
            }

            if (oldToNew.contains(current)) {
                return oldToNew[current];
            }
            
            Node* clone = new Node(current->val);
            oldToNew[current] = clone;

            std::vector<Node*> childrens{};
            for (auto child : current->neighbors) {
                childrens.push_back(dfs(child));
            }

            clone->neighbors = std::move(childrens);
            return clone;
        };

        return dfs(node);
    }
};