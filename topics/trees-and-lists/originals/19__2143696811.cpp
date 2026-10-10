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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        int length = 0;
        while (current) {
            ++length;
            current = current->next;
        }

        current = head;

        if (length - n == 0) {
            return head->next;
        }

        int i = 0;
        while (current) {
            if (i++ == length - n) {
                prev->next = current->next;
                break;
            }

            prev = current;
            current = current->next;
        }

        return head;
    }
};