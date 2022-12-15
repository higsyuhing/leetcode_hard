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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k == 1)
            return head; 
        ListNode *newhead = head; 
        vector<ListNode *> array(k, nullptr); 

        int pos = 0; 
        ListNode *curr = head; 
        ListNode *lasthead = nullptr; 
        ListNode *nextcurr = nullptr; 
        bool flag = true; 
        while (1){
            for (int i = 0; i < k; i++){
                if (curr == nullptr){
                    flag = false; 
                    break; 
                }
                array[i] = curr; 
                curr = curr->next; 
            }
            if (flag == false){
                break; 
            }

            if (newhead == head){
                newhead = array[k-1]; 
            }
            nextcurr = array[k-1]->next; 
            for (int i = 1; i < k; i++){
                array[i]->next = array[i-1]; 
            }
            array[0]->next = nextcurr; 
            if (lasthead != nullptr){
                lasthead->next = array[k-1]; 
            }
            lasthead = array[0]; 
            curr = nextcurr; 
        }

        return newhead; 
    }
};
