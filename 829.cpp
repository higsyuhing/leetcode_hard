class Solution {
public:
    int consecutiveNumbersSum(int N) {
        // assume N can use m consecutive numbers adding up. 
        // saying starts from x, x+1, x+2, ..., x+m-1
        // Thus sum will be: m*x + (0+m-1)*m/2 = N
        // solving this function from m = 1 -> K, by then: 
        // (K-1)*K/2 >= N, thus x will be less than 0. 
        // note that x should >0 positive integers
        
        int ret = 1; // start from 2, 1 always there. 
        int m, x, temp; 
        
        m = 2; 
        while(1){
            temp = (m-1)*m/2; 
            temp = N - temp; 
            if(temp <= 0) break; 
            if((temp%m) == 0) ret++; 
            m++; 
        }
        
        return ret; 
    }
};
