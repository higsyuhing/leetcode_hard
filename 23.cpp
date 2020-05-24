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
	struct comp
	{
		bool operator () (const ListNode* a, const ListNode* b)
		{
			return a->val > b->val;
		}
	};
    
    
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // use pq.. not hard..
        ListNode *res, *curr, *temp; 
        priority_queue<ListNode *, vector<ListNode *>, comp> queue_heads;
        
        // init load
        for(int i = 0; i < lists.size(); i++){
            if(lists[i] != NULL)
                queue_heads.push(lists[i]); 
        }
        
        res = new ListNode(); //fake head
        curr = res; 
        while(!queue_heads.empty()){
            temp = queue_heads.top(); 
            queue_heads.pop(); 
            
            curr->next = temp; 
            curr = temp; 
            if(temp->next != NULL){
                queue_heads.push(temp->next); 
            }
        }
        
        curr = res->next; 
        delete res; 
        return curr; 
    }
};
