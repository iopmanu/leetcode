/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}

        1 -> 2 -> 3 -> 4 -> 5
        1, 1
        2, 3
        3, 5

 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head; ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                return true;
            }
        }

        return false;
    }
};