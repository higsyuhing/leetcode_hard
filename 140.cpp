class Solution {
public:
    
    unordered_set<int> visit;
    vector<vector<int>> g;
    vector<string> vans;
    
    void dfs(int i, string &s, string ans) {
        if(i == s.size()) {
            ans.pop_back();
            vans.push_back(ans);
            return;
        }
        visit.insert(i);
        for(auto j : g[i]) {
            if(visit.count(j) == 0) {
                dfs(j, s, ans + s.substr(i, j - i) + " ");
            }
        }
        visit.erase(i);
    }
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if(s.empty() || wordDict.empty())
            return {};
        int n = s.size();
        g.resize(n + 1);
        unordered_set<string> us;
        for(auto &i : wordDict) {
            reverse(i.begin(), i.end());
            us.insert(i);
        }
        vector<bool> dp(n + 1);
        dp[0] = true;
		// build graph, similar to word break
        for(int i = 1; i <= n; ++i) {
            string str;
            for(int j = i; j >= 0; --j) {
                if(dp[j] && us.count(str)) {
                    g[j].push_back(i);
                    dp[i] = true;
                }
                if(j)
                    str += s[j - 1];
            }
        }
        if(!dp[n])
            return {};
		// traverse all the paths
        dfs(0, s, "");
        return vans;
    }
};

/*
check discussion: 
https://leetcode.com/problems/word-break-ii/discuss/44167/My-concise-JAVA-solution-based-on-memorized-DFS

*/
