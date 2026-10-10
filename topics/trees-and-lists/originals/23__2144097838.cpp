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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::deque<ListNode*> nodes{};
        for (ListNode* node : lists) {
            if (node) {
                nodes.push_back(node);
            }
        }

        if (nodes.empty()) {
            return nullptr;
        }

        std::function<ListNode*(ListNode*, ListNode*)> merge = [&](ListNode* l, ListNode* r) {
            ListNode* retval = new ListNode(0);
            ListNode* head = retval;

            while (l && r) {
                if (l->val > r->val) {
                    head->next = r;
                    head = head->next;
                    r = r->next;
                } else {
                    head->next = l;
                    head = head->next;
                    l = l->next;
                }
            }

            head->next = l ? l : r;

            head = retval->next;
            delete retval;

            return head;
        };

        while (nodes.size() > 1) {
            ListNode* l = nodes.front();
            nodes.pop_front();
            ListNode* r = nodes.front();
            nodes.pop_front();

            nodes.push_back(merge(l, r));
        }

        return nodes.back();
    }
};