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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lengthA = 0;
        ListNode *tmpA = headA;
        while (tmpA)
        {
            lengthA++;
            tmpA = tmpA->next;
        }
        int lengthB = 0;
        ListNode *tmpB = headB;
        while (tmpB)
        {
            lengthB++;
            tmpB = tmpB->next;
        }
        
        tmpA = headA;
        tmpB = headB;
        if (lengthA > lengthB)
        {
            int length_delta = lengthA - lengthB;
            while (length_delta > 0)
            {
                tmpA = tmpA->next;
                length_delta--;
            }
        }
        else if (lengthA < lengthB)
        {
            int length_delta = lengthB - lengthA;
            while (length_delta > 0)
            {
                tmpB = tmpB->next;
                length_delta--;
            }
        }
        
        while(tmpA)
        {
            if (tmpA == tmpB) return tmpA;
            else
            {
                tmpA = tmpA->next;
                tmpB = tmpB->next;
            }
        }
        
        return NULL;
    }
};
