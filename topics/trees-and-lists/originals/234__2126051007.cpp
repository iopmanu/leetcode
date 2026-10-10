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
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow;
        ListNode* prev = nullptr;
        while (mid) {
            ListNode* tmp = mid->next;
            mid->next = prev;
            prev = mid;
            mid = tmp;
        }

        ListNode* tail = prev;
        while (head && tail && tail != head) {
            if (head->val != tail->val) {
                return false;
            }

            head = head->next;
            tail = tail->next;
        }

        return true;
    }
};