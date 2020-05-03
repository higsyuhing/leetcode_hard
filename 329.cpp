class Solution {
public:
    int rows, cols;
    vector<vector<int>>dp;
    int res = 0;
    
    void dfs(vector<vector<int>>& matrix, int i, int j, int len, vector<int>&v) {
        
        if (i >= rows || i < 0 || j >= cols || j < 0 || dp[i][j] > len) return;
        if (v.size() && v.back() >= matrix[i][j]) return;
        
        len++;
        dp[i][j] = max(dp[i][j], len);
        res = max(res, len);
        v.push_back(matrix[i][j]);
        dfs(matrix, i+1, j, len, v);
        dfs(matrix, i-1, j, len, v);
        dfs(matrix, i, j+1, len, v);
        dfs(matrix, i, j-1, len, v);
        v.pop_back();
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // naive: loop all position as starting point
        //      then dfs to find the maximum length
        // but note that, some increasing order is shared.. 
        // thus DP. remember each position's result.. 
        //      if we reach the previously accessed position, directly add result
        
        
        if (matrix.empty()) return 0;
        
        rows = matrix.size();
        cols = matrix[0].size();

        dp.resize(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                vector<int>v;
                dfs(matrix, i, j, 0, v);
            }
        }
        
        return res;
    }
};

/*
// some tricky speed-up..

static auto speedup = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int n,m;
    vector<vector<int>> mp;
    int dfs(vector<vector<int>>& matrix, int i, int j){
        // string s;
        // s+=i+48;
        // s+='x';
        // s+=j+48;
        // cout<<s<<endl;
        
        if (mp[i][j]!=-1) return mp[i][j];
        int a=0,b=0,c=0,d=0;
        if (i>0 && matrix[i-1][j]>matrix[i][j]) a=dfs(matrix, i-1, j);
        if (j>0 && matrix[i][j-1]>matrix[i][j]) b=dfs(matrix, i, j-1);
        if (i<n-1 && matrix[i+1][j]>matrix[i][j]) c=dfs(matrix, i+1, j);
        if (j<m-1 && matrix[i][j+1]>matrix[i][j]) d=dfs(matrix, i, j+1);
        return mp[i][j]=1+max(max(a,b), max(c, d));
        // mp[i][j]=x;
        // cout<<s<<" - "<<mp[s]<<endl;
        // return x;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int res=0;
        n=matrix.size();
        if (n==0) return 0;
        m=matrix[0].size();
        if (m==0) return 0;
        // unordered_map<string, int> mp;
        mp=vector(n, vector<int>(m, -1));
        int x=0;
        for (int i=0; i<n; ++i){
            for (int j=0; j<m; ++j){
                x=dfs(matrix, i, j);
                res = res>x?res:x;
            }
        };
        return res;
    }
};

*/

