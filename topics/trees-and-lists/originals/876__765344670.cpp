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
    ListNode* middleNode(ListNode* head) {
        int array[100];
        int length = 0;

        ListNode *tmp = head;

        while(tmp != NULL) {
            array[length++] = tmp->val;
            tmp = tmp->next;
        }

        /*if (length % 2 == 0) {
            length /= 2;
        } else {
            length /= 2;
            length++;
        }*/
        
        length /= 2;

        tmp = head;

        while (tmp != NULL && length > 0) {
            tmp = tmp->next;
            length--;
        }

        return tmp;
        
    }
};
