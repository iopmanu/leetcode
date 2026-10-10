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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int reminder = 0;

        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        while (l1 && l2) {
            int sum = l1->val + l2->val + reminder;
            current->next = new ListNode(sum % 10);
            current = current->next;
            reminder = sum / 10;

            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1) {
            int sum = l1->val + reminder;
            current->next = new ListNode(sum % 10);
            current = current->next;
            reminder = sum / 10;

            l1 = l1->next;
        }

        while (l2) {
            int sum = l2->val + reminder;
            current->next = new ListNode(sum % 10);
            current = current->next;
            reminder = sum / 10;

            l2 = l2->next;
        }

        if (reminder) {
            current->next = new ListNode(reminder);
        }

        current = dummy->next;
        delete dummy;

        return current;
    }
};