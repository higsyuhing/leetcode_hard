class Solution {
public:
    typedef struct node { 
        int data, count;
        node *left, *right; 
        public: 
            node(int value) { 
                data = value; 
                left = right = NULL; 
                count=0;
            } 
        }node;
  
    node* insert(node *root, int value, int* less, int greater) { 
        if(!root) 
        { 
            *less=greater;
            return new node(value); 
        } 
  
        if(value <= root->data) 
        {
            root->count++;
            root->right = insert(root->right, value, less, greater); 
        } 
        else root->left = insert(root->left, value, less, greater+root->count+1);
        return root; 
    } 
    
    vector<int> countSmaller(vector<int>& nums) {
        // I can feel there is an algo behind it.. but I don't know what/how
        // naive: compare and count.. this is stupid. 
        // how do we reuse previous comparison result??? 
        
        // a DP? if a[n] > a[i], it still need to check if any between a[i] a[n]
        // no.. not reuse the result.. 
        
        vector<int> ans(nums.size());
        node* root=NULL;
        for(int i=nums.size()-1;i>=0;i--){
            int less=0;
            root=insert(root, nums[i], &less, 0);
            ans[i]=less;
        }
        return ans;
    }
};

/*
There are 2 key insights:
- Move right to left
- Pass the count of numbers smaller than that node to the new node

smart!! why I cannot come up with this kind of structure.. 
*/
