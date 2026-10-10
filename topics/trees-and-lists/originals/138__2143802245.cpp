/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        std::unordered_map<Node*, Node*> mapping{};
        Node* current = head;
        while (current) {
            mapping[current] = new Node(current->val);
            current = current->next;
        }

        current = head;

        while (current) {
            mapping[current]->next = mapping[current->next];
            mapping[current]->random = mapping[current->random];

            current = current->next;
        }

        return mapping[head];
    }
};

// >= n || < 0 => n + 1;
// 