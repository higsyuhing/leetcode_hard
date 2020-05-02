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
    void checktree(TreeNode *node, int *maxpathptr, int *maxpathnodeptr){
        // node is always valid! 
        int leftpath, leftpathnode, rightpath, rightpathnode; 
        int temp, temp1; 
        //cout << node->val << endl; 
        
        if((node->left == NULL) && (node->right == NULL)){
            *maxpathptr = node->val; 
            *maxpathnodeptr = node->val; 
            return; 
        }
        if(node->left == NULL){
            checktree(node->right, &rightpath, &rightpathnode); 
            temp1 = rightpathnode + node->val; 
            *maxpathnodeptr = (node->val > temp1)?(node->val):temp1; 
            *maxpathptr = (rightpath>(*maxpathnodeptr))?rightpath:(*maxpathnodeptr);
            return; 
        }
        if(node->right == NULL){
            checktree(node->left, &leftpath, &leftpathnode); 
            temp1 = leftpathnode + node->val; 
            *maxpathnodeptr = (node->val > temp1)?(node->val):temp1; 
            *maxpathptr = (leftpath>(*maxpathnodeptr))?leftpath:(*maxpathnodeptr);
            return; 
        }
        
        checktree(node->left, &leftpath, &leftpathnode); 
        checktree(node->right, &rightpath, &rightpathnode); 
        //cout << "curr: " << node->val << " leftpath: " << leftpath << 
        //    " leftpathnode: " << leftpathnode << " rightpath: " << rightpath
        //    << " rightpathnode: " << rightpathnode << endl; 
        
        temp = (leftpathnode > rightpathnode) ? leftpathnode : rightpathnode; 
        temp += node->val; 
        *maxpathnodeptr = (temp > node->val) ? temp : node->val; 
        
        
        temp = (leftpath > rightpath) ? leftpath : rightpath; 
        temp1 = leftpathnode + rightpathnode + node->val; 
        temp1 = (temp1 > (*maxpathnodeptr)) ? temp1 : (*maxpathnodeptr); 
        temp = (temp > temp1) ? temp : temp1; 
        
        *maxpathptr = temp; 
        return; 
    }
    
    int maxPathSum(TreeNode* root) {
        // recursive: the maximum appears in: 
        //      p1. pure in left subtree
        //      p2. maximum path ended by node.left
        //      p3. pure in right subtree
        //      p4. maximum path ended by node.right
        //      then for the current node, returns: 
        //      max path ended to this node: max{p2, p4} + val
        //      max path: max{p1, p3}, max{p2+val, p4+val, p2+p4+val}
        
        if(root == NULL) return 0; 
        
        int maxpath, maxpathnode; 
        checktree(root, &maxpath, &maxpathnode); 
        return maxpath; 
    }
};


/*
// what the hell???

#pragma GCC optimize ("Ofast")
static auto _ = [] { std::ios::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0); return 0; } ();

class Solution {
public:
    int helper(TreeNode* root, int &maxsum) {
        if(!root) return 0;
        int l = helper(root->left, maxsum);
        int r = helper(root->right, maxsum);
        
        if(l<0) l=0;
        if(r<0) r=0;
        
        if (l + root->val + r >maxsum) 
            maxsum = l + root->val + r;
        
        if (l>r) return root->val + l;
        else return root->val + r;
    }
    int maxPathSum(TreeNode* root) {
        if(!root) return 0;
        int maxsum = root->val;
        helper(root, maxsum);
        return maxsum;
    }
};

*/
