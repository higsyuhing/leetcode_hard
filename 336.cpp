// I have no idea... :(

class Solution {
public:
    bool isPalindrome(string A){
        int l = 0;
        int r = A.size()-1;
        while(l<r){
            if(A[l++]!=A[r--]) return false;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int N = words.size();
        unordered_map<string,int> MAP;
        vector<vector<int>> ANS;
        for(int j=0;j<N;j++) MAP[words[j]] = j;
        for(int j=0;j<N;j++){
            int M = words[j].size();
            for(int i=0;i<M;i++){
                if(isPalindrome(words[j].substr(0,i+1))){
                    string right = (M-i-1 > 0 ? words[j].substr(i+1,M-i-1) : "");
                    reverse(right.begin(),right.end());
                    if(MAP.find(right)!=MAP.end()){
                        ANS.push_back({MAP[right],j});
                    }
                }
                
                if(isPalindrome(words[j].substr(i,M-i))){
                    string left = (i==0 ? "" : words[j].substr(0,i));
                    reverse(left.begin(),left.end());
                    if(MAP.find(left)!=MAP.end()){
                        ANS.push_back({j,MAP[left]});
                    }
                }                                
            }
            string p = words[j];
            reverse(p.begin(), p.end());
            if(MAP.find(p)!=MAP.end()){
                if(j!=MAP[p]) ANS.push_back({j,MAP[p]});
            }
        }
        return ANS;
    }
}; 
