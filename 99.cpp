/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode *node11, *node12, *node21, *node22, *curr1, *curr2; 
    bool completeflag; 
    
    void traversal(TreeNode* node){
        if(completeflag) return; 
        
        if(node->left){
            traversal(node->left); 
        }
        
        // do recording
        if(curr1 == NULL) curr1 = node; // no comparison
        else if(curr2 == NULL){
            curr2 = node; 
            // do comparison
            if(curr1->val > curr2->val){
                if(node11 == NULL){
                    node11 = curr1; 
                    node12 = curr2; 
                }
                else{
                    // finish record, complete
                    node21 = curr1; 
                    node22 = curr2; 
                    completeflag = true; 
                }
            }
        }
        else{
            // move the previous one
            curr1 = curr2; 
            curr2 = node; 
            // do comparison
            if(curr1->val > curr2->val){
                if(node11 == NULL){
                    node11 = curr1; 
                    node12 = curr2; 
                }
                else{
                    // finish record, complete
                    node21 = curr1; 
                    node22 = curr2; 
                    completeflag = true; 
                }
            }
        }
        
        if(node->right){
            traversal(node->right); 
        }
    }
    
    
    void recoverTree(TreeNode* root) {
        if(root == NULL) return; 
        
        node11 = NULL; 
        node12 = NULL; 
        node21 = NULL; 
        node22 = NULL; 
        curr1 = NULL; 
        curr2 = NULL; 
        completeflag = false; 
        
        traversal(root); 
        
        if(node21 == NULL){
            // just swap node11/node12
            int value = node12->val; 
            node12->val = node11->val; 
            node11->val = value; 
        }
        else{
            // swap node11/node22
            int value = node22->val; 
            node22->val = node11->val; 
            node11->val = value; 
        }
    }
};
