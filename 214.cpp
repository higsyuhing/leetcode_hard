class Solution {
public:
    // OK.. I am slow  = =
    string shortestPalindrome(string s){
        int n = s.size();
        string rev(s);
        reverse(rev.begin(), rev.end());
        string s_new = s + "#" + rev;
        int n_new = s_new.size();
        vector<int> f(n_new, 0);
        for (int i = 1; i < n_new; i++) {
            int t = f[i - 1];
            while (t > 0 && s_new[i] != s_new[t])
                t = f[t - 1];
            if (s_new[i] == s_new[t])
                ++t;
            f[i] = t;
        }
        return rev.substr(0, n - f[n_new - 1]) + s;
    }
    
    /*
    bool isPalindromic(string& s, int i, int j){
        // string s [i,j) is isPalindromic? 
        if(i >= j) return false; 
        int a, b; 
        for(a = i, b = j-1; a < b; a++, b--){
            if(s[a] != s[b]) return false; 
        }
        return true; 
    }
    
    string shortestPalindrome(string s) {
        // starting from the end, delete last several chars and see: 
        //      if the remaining isPalindrome
        // if yes, thus we get the longest for this, 
        //      thus reverse the deleted char and add into the front.. 
        
        int i;
        for(i = s.size(); i > 0; i--){
            if(isPalindromic(s, 0, i)) break; 
        }
        // thus s[0:i) is Palindrome
        string temp = ""; 
        for(; i < s.size(); i++){
            temp = s[i] + temp; // reversed
        }
        
        return temp + s; 
    }
    */
};
