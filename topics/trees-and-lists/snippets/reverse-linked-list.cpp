    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        while(current) {
            ListNode* tmp = current->next;
            current->next = prev;
            prev = current;
            current = tmp;
        }

        return prev;
    }
