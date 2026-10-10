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
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* current = head;
        ListNode* reverse = nullptr;

        while (current != nullptr) {
            if (reverse == nullptr) {
                reverse = current;
            } else {
                ListNode* reverseTmp = reverse;
                reverse = new ListNode(current->val, reverseTmp);
            }

            current = current->next;
        }

        head->next = nullptr; 

        return reverse;
    }
};