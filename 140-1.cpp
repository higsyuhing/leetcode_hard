class Solution {
public:

    void backtrack(vector<string>& ret, vector<bool>& dp, unordered_set<string>& dict, 
        string& s, vector<string>& stack, int pos, int maxlen){
        
        if (pos == 0){
            // record the stack and put into the ret, return
            string tmp = ""; 
            for (auto it = stack.rbegin(); it != stack.rend(); it++){
                tmp += (*it + " "); 
            }
            tmp.pop_back(); // last " ", s.length >= 1, guarantee there is a word
            ret.push_back(tmp); 
            return; 
        }

        for(int j=pos-1; (j>=0 && j>(pos-1-maxlen)); j--){
            if(dp[j]){
                string word = s.substr(j,pos-j);
                if(dict.find(word) != dict.end()){
                    // dp[i]=true;
                    // break; // no break, we need to find all potential cases
                    stack.push_back(word); 
                    backtrack(ret, dp, dict, s, stack, j, maxlen); 
                    stack.pop_back(); 
                }
            }
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // no.. DP
        vector<bool> dp(s.size()+1, false); 
        dp[0] = true; // [, 0) is true
        unordered_set<string> dict; 
        int maxlen = 0; 
        for (string& word : wordDict){
            dict.insert(word); 
            maxlen = (word.size() > maxlen) ? word.size() : maxlen; 
        }

        for(int i=1;i<=s.size();i++)
        {
            for(int j=i-1;(j>=0 && j>(i-1-maxlen));j--)
            {
                if(dp[j])
                {
                    string word = s.substr(j,i-j);
                    if(dict.find(word)!= dict.end())
                    {
                        dp[i]=true;
                        break; //next i
                    }
                }
            }
        }
        
        vector<string> ret; 
        if (dp[s.size()] == false)
            return ret; 
        
        vector<string> stack; 
        backtrack(ret, dp, dict, s, stack, s.size(), maxlen); 
        return ret; 
    }
};
