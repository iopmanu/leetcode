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
    struct Compare {
        bool operator()(ListNode* l, ListNode* r) {
            return l->val > r->val;
        }
    };

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::priority_queue<ListNode*, std::vector<ListNode*>, Compare> pq{};
        for (ListNode* l : lists) {
            while (l) {
                pq.push(l);
                l = l->next;
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        while (!pq.empty()) {
            current->next = pq.top();
            pq.pop();

            current = current->next;
            current->next = nullptr;
        }

        current = dummy->next;
        delete dummy;

        return current;
    }
};