class Solution {
public:
    int trap(vector<int>& height) {
        
        int len = height.size(); 
        if(len < 2) return 0; // never be able to hold water
        
        int maxindex, i, max; 
        max = 0; 
        for(i = 0; i < len; i++){
            if(height[i] > max){
                max = height[i]; 
                maxindex = i; 
            }
        }
        
        int currval, accu; 
        accu = 0; 
        
        currval = 0; 
        for(i = 0; i < maxindex; i++){
            if(height[i] > currval) currval = height[i]; 
            else accu += (currval - height[i]); 
        }
        
        currval = 0; 
        for(i = len-1; i > maxindex; i--){
            if(height[i] > currval) currval = height[i]; 
            else accu += (currval - height[i]); 
        }
        
        return accu; 
    }
};
