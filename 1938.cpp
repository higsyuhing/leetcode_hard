struct TrieNode {
    int child[2] = {};
    int go = 0; // Number of elements goes through this node
};

vector<TrieNode> triePool;
int trieNextId = 2;
void initTrie(int capacity) {
    triePool.resize(18 * capacity + 5);
}
void increase(int number, int d) {
    int cur = 1;
    for (int i = 17; i >= 0; --i) {
        int bit = (number >> i) & 1;
        if (triePool[cur].child[bit] == 0) {
            triePool[cur].child[bit] = trieNextId++;
        }
        cur = triePool[cur].child[bit];
        triePool[cur].go += d;
    }
}
int findMax(int number) {
    int ans = 0, cur = 1;
    for (int i = 17; i >= 0; --i) {
        int bit = (number >> i) & 1;
        if (triePool[cur].child[1 - bit] != 0 && triePool[triePool[cur].child[1 - bit]].go > 0) {
            cur = triePool[cur].child[1 - bit];
            ans |= (1 << i);
        } else cur = triePool[cur].child[bit];
    }
    return ans;
}

class Solution { // 484 ms, faster than 100.00%
public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& qs) {
        int n = parents.size(), m = qs.size(), root = -1;
        initTrie(n);
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; ++i)
            if (parents[i] == -1) root = i;
            else graph[parents[i]].push_back(i);
        vector<vector<pair<int, int>>> queryByNode(n);
        for (int i = 0; i < m; ++i)
            queryByNode[qs[i][0]].push_back(make_pair(qs[i][1], i)); // node -> list of pairs (val, idx)

        vector<int> ans(m);
        dfs(root, graph, queryByNode, ans);
        return ans;
    }
    void dfs(int u, vector<vector<int>>& graph, vector<vector<pair<int, int>>>& queryByNode, vector<int>& ans) {
        increase(u, 1);
        for (auto& p : queryByNode[u])
            ans[p.second] = findMax(p.first);
        for (int& v : graph[u])
            dfs(v, graph, queryByNode, ans);
        increase(u, -1);
    }
};


/*
// give it up.. this one is too hard.. 

class Solution {
public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        
        // basic version: 
        // just jump in the "parents" array. 
        
        vector<int> results; 
        for(auto it = queries.begin(); it != queries.end(); it++){
            vector<int>& query = *it; 
            int node = query[0]; 
            int val = query[1]; 
            
            int result = node ^ val; 
            while(parents[node] != -1){
                node = parents[node]; 
                result = (result < (node ^ val)) ? (node ^ val) : result; 
            }
            
            results.push_back(result); 
        }
        
        return results; 
    }
};

https://leetcode.com/problems/maximum-genetic-difference-query/discuss/1344913/C%2B%2BJavaPython-DFS-and-Trie-and-Compute-queries-by-nodes-Clean-and-Concise

*/
