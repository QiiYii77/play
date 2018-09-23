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
    ListNode* reverseList(ListNode* head) {
        if (!head) return head;
        ListNode *p1 = head;
        ListNode *p2 = p1->next;
        if (!p2) return p1;
        ListNode *p3 = p2->next;
        
        p1->next = NULL;
        while (p3)
        {
            p2->next = p1;
            p1 = p2;
            p2 = p3;
            p3 = p3->next;
        }
        p2->next = p1;
        return p2;
    }
};
