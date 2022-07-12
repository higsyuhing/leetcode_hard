class Solution {
public:
    
    
    // return 0: not found yet; return 1: found it. 
    int helper_findcycle(int curr, int parent, int color[], int par[], 
                         vector<vector<int>>& graph, vector<int>& cycle){
        
        // if done, return. 
        if (color[curr] == 2) return 0; 
        
        if (color[curr] == 1){
            // visit this one currently and touch the cycle. we find it. 
            int tmp = parent; 
            cycle.push_back(curr); 
            while (curr != tmp){
                cycle.push_back(tmp); 
                tmp = par[tmp]; 
            }
            return 1; 
        }
        
        // color == 0, new node
        par[curr] = parent; 
        color[curr] = 1; 
        
        for (int next : graph[curr]){
            if (next == parent) continue; 
            int ret = helper_findcycle(next, curr, color, par, graph, cycle); 
            if (ret == 1) return 1; 
        }
        
        color[curr] = 2; 
        return 0; 
    }
    
    
    
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        
        // 2 steps: 1. find the cycle: array of nodes
        //          2. compute the distance
        
        vector<vector<int>> graph; 
        vector<int> tmp; 
        for (int i = 0; i < n; i++) graph.push_back(tmp); 
        
        for (auto edge : edges){
            int u, v; 
            u = edge[0]; v = edge[1]; 
            graph[u].push_back(v); 
            graph[v].push_back(u); 
        }
        
        // step 1
        int par[n], color[n]; 
        for (int i = 0; i < n; i++){
            par[i] = -1; 
            color[i] = 0; 
        }
        vector<int> cycle; 
        
        helper_findcycle(0, -1, color, par, graph, cycle); 
        
        // debug test
        // cout << "done" << endl; 
        // cout << "cycle id: "; 
        // for (int node : cycle){
        //     cout << node << " "; 
        // }
        // cout << endl; 
        
        
        // step 2. compute the distance
        // a BFS? use map/set as an iterator.. 
        // algo: 
        //      1. complete map: init with cycle nodes with 0
        //      count = size(cycle); curr_set = cycle nodes
        //      while: complete map count == n. 
        
        vector<int> result; 
        for (int i = 0; i < n; i++) result.push_back(-1); 
        set<int> currset; 
        for (int node : cycle){
            result[node] = 0; 
            currset.insert(node); 
        }
        
        set<int> nextset; 
        set<int> *currset_ptr, *nextset_ptr; 
        currset_ptr = &currset; 
        nextset_ptr = &nextset; 
        
        int dist = 1; 
        while(currset_ptr->size() > 0){
            // nextset must has size 0. 
            // find all not counted neighbors, mark results
            for (int node : *currset_ptr){
                for (int next : graph[node]){
                    if (result[next] == -1){
                        // set: redundant neighbors are auto-eliminated
                        nextset_ptr->insert(next); 
                        result[next] = dist; 
                    }
                }
            }
            
            // dist + 1
            dist++; 
            
            // update currset, swap ptr. 
            currset_ptr->clear(); 
            set<int> *tmp_ptr = currset_ptr; 
            currset_ptr = nextset_ptr; 
            nextset_ptr = tmp_ptr; 
        }
        
        
        return result; 
    }
};


/*
https://leetcode.com/problems/distance-to-a-cycle-in-undirected-graph/discuss/1894719/Outside-In-and-Inside-Out

vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
    vector<vector<int>> al(n);
    vector<int> res(n, 0), cnt(n);
    queue<int> q;
    for (auto &e : edges) {
        al[e[0]].push_back(e[1]);
        al[e[1]].push_back(e[0]);
    }
    for (int i = 0; i < n; ++i) {
        cnt[i] = al[i].size();
        if (cnt[i] == 1)
            q.push(i);        
    }
    while (!q.empty()) {
        int i = q.front(); q.pop();
        res[i] = INT_MAX;
        for (int j : al[i])
            if (cnt[j] > 1 && --cnt[j] == 1)
                q.push(j);
    }
    for (int i = 0; i < n; ++i)
        if (cnt[i] > 1)
            q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for (int j : al[i])
            if (res[j] > res[i] + 1) {
                res[j] = res[i] + 1;
                q.push(j);
            }
    }
    return res;
}

smart idea but using outside-in is not correct. 
e.g.: 

[0,1] - [1,2] - [2,3] - [3-4] - [4,6] - [6,7] - [7,8] - [... a cycle]...
                [2,5] - [5-4]

then node 6, 7 are between two cycles and will not be found (count as part of cycle). 
then the distance between 6/7 to loops are non-zero. 
but outside-in will count them as 0. 

*/




