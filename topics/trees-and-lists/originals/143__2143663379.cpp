/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        std::deque<ListNode*> nodes{};
        ListNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }

        std::unordered_set<ListNode*> visited{};
        current = head;
        while (!nodes.empty()) {
            ListNode* even = nodes.back();
            visited.insert(current);
            if (visited.contains(even)) {
                current->next = nullptr;
                break;
            }

            nodes.pop_back();
            
            ListNode* next = current->next;
            if (visited.contains(next)) {
                current->next = nullptr;
                break;
            }

            current->next = even;
            even->next = next;
            current = next;
        }
    }
};