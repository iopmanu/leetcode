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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* current = head;
        for (int i = 0; i < k; ++i) {
            if (!current) {
                return head;
            }

            current = current->next;
        }

        current = head;
        ListNode* prev = nullptr;
        ListNode* nextNode = nullptr;
        for (int i = 0; i < k; ++i) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }

        if (nextNode) {
            head->next = reverseKGroup(nextNode, k);
        }

        return prev;
    }
};