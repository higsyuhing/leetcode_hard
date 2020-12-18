class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.size() == 0) return 1; 
        // in-place put
        for(int i = 0; i < nums.size(); ){
            int curr = nums[i]; 
            // swap with nums[curr-1]
            if((curr > 0) && (curr <= nums.size())){
                int temp = nums[curr-1]; 
                if(temp == curr){
                    if(curr != (i+1)) nums[i] = 0; 
                    i++; 
                    continue; 
                }
                nums[curr-1] = curr; 
                nums[i] = temp; 
                if(curr < (i+1)) i++; 
            }
            else{
                nums[i] = 0; 
                i++; 
            }
        }
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == 0) return (i+1); 
        }
        return (nums.size()+1);
    }
};

/*
// use hash can be O(n) time/space
    int firstMissingPositive(vector<int>& nums) {
        int hasharray[300]; // i+1 -> occur or not
        for(int i = 0; i < 300; i++) hasharray[i] = 0; 
        for(int i = 0; i < nums.size(); i++){
            int curr = nums[i];
            if((curr > 0) && (curr <= 300)){
                hasharray[curr-1] = 1; 
            }
        }
        for(int i = 0; i < 300; i++){
            if(hasharray[i] == 0) return (i+1); 
        }
        return 0;
    }

*/
