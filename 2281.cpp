class Solution {
public:
    int totalStrength(vector<int>& strength) {
        
        // it's a triangle.. use 2 arrays for the sum and min
        
        // vector<int> sum(strength.begin(), strength.end()); 
        // vector<int> min(strength.begin(), strength.end()); 
        
        vector<long long> sumarr(strength.size(), 0); 
        vector<int> minarr(strength.size(), 0); 
        long long res = 0; 
        long long MOD = 1e9 + 7; 
        
        for (int off = 0; off < strength.size(); off++)
        {
            for (int start = 0; start < (strength.size() - off); start++)
            {
                sumarr[start] = (sumarr[start] + (long long)strength[start + off]) % MOD; 
                if (off == 0)
                    minarr[start] = strength[start + off]; 
                else
                    minarr[start] = min(minarr[start], strength[start + off]); 
                
                res = (res + (sumarr[start]*((long long)minarr[start])) % MOD) % MOD; 
                // cout << sumarr[start] << ", " << minarr[start] << ", " << res << endl; 
            }
        }
        
        return (int)res; 
    }
};


/*
TLE. see the solution, this one is similar to  84. Largest Rectangle in Histogram.
https://leetcode.com/problems/sum-of-total-strength-of-wizards/discuss/2061787/Amazon-Online-Assessment

*/


