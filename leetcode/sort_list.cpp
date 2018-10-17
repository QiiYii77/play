/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        return quickSortList(head, NULL);
    }
    
    ListNode *quickSortList(ListNode *start, ListNode *end)
    {
        if (!start) return NULL;
        if (start == end) return start;
        ListNode *head = start;
        ListNode *middle = start;
        ListNode *previous = start;
        ListNode *current = start->next;
        while (current != end)
        {
            if (current->val < middle->val)
            {
                ListNode *p = current->next;
                current->next = head;
                head = current;
                current = p;
                previous->next = p;
            }
            else   
            {
                previous = current;
                current = current->next;
            }
        }
        head = quickSortList(head, middle);
        middle->next = quickSortList(middle->next, end);
        return head;
    }
};
