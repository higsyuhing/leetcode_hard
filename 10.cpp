class Solution {
public:
    bool isMatch(string s, string p) {
        // lexical analysis.. 
        // construct a transaction table T, and state S
        // match the entire string makes it easier
        // update: I don't think T/S is a solution, since forwarding will
        //          generate a lot of redundant states. -> timeout
        int n = s.length();
        int m = p.length();
        bool dp[n+1][m+1];
        memset(dp, false, sizeof(dp));
        dp[0][0] = true;
        for(int i=1;i<=n;i++)
        {
            dp[i][0] = false; 
        }

        for(int i=2;i<=m;i++)
        {
            if(p[i-1]=='*'&&dp[0][i-2])
            {
                dp[0][i] = true;
            }
        }

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(s[i-1]==p[j-1]||p[j-1]=='.')
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else if(p[j-1]=='*')
                {
                   dp[i][j] = dp[i][j-2] ||(s[i-1]==p[j-2]&&dp[i-1][j])||(p[j-2]=='.'&&dp[i-1][j]);
                }
                else
                {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
        
    }
};

/*
check this DP solution!! 


*/
