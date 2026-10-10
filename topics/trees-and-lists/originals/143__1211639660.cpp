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
        stack<ListNode *> stk;
        auto current = head;

        while (current) {
            stk.push(current);
            current = current->next;
        }

        current = head;
        unordered_map<ListNode*, bool> visited;

        while (true) {
            auto last = stk.top();
            stk.pop();
            auto next = current->next;
            visited[current] = true;

            if (visited[last]) {
                current->next = nullptr;
                break;
            }

            current->next = last;
            visited[last] = true;
            current = current->next;

            if (visited[next]) {
                current->next = nullptr;
                break;
            }

            current->next = next;
            current = current->next;
        }
    }
};