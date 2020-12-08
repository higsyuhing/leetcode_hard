class Solution {
public:
    
    int helper_recursive(map<int, int>& fastcheck, int curr){
        if(fastcheck.find(curr) != fastcheck.end()) return fastcheck[curr]; 
        
        int div2path = curr%2 + helper_recursive(fastcheck, curr/2); 
        int div3path = curr%3 + helper_recursive(fastcheck, curr/3); 
        int res = 1 + (div2path > div3path ? div3path : div2path); 
        fastcheck[curr] = res; 
        //cout << curr << " " << res << endl; 
        return res; 
    }
    
    
    int minDays(int n) {
        if(n == 1) return 1; 
        
        map<int, int> fastcheck; 
        fastcheck[0] = 0; 
        fastcheck[1] = 1; 
        
        return helper_recursive(fastcheck, n); 
        
        // if n very large, no need to compute [n/2, n] or [n/3, n]
        /*
        vector<int> dp(n); 
        dp[0] = 1; // init
        
        for(int i = 2; i <= n; i++){
            int curr = dp[i-2]+1; 
            if(i % 2 == 0){
                curr = min(curr, dp[i/2-1]+1); 
            }
            if(i % 3 == 0){
                curr = min(curr, dp[i/3-1]+1); 
            }
            dp[i-1] = curr; 
            //cout << curr << " "; 
        }
        return dp[n-1]; 
        */
    }
};
