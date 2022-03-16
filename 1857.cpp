// OJ: https://leetcode.com/contest/weekly-contest-240/problems/largest-color-value-in-a-directed-graph/
// Author: github.com/lzl124631x
// Time: O(V + E)
// Space: O(V + E)
class Solution {
    typedef array<int, 26> T;
public:
    int largestPathValue(string C, vector<vector<int>>& E) {
        unordered_map<int, vector<int>> G;
        vector<int> indegree(C.size());
        for (auto &e : E) {
            G[e[0]].push_back(e[1]); // build graph
            indegree[e[1]]++; // count indegrees
        }
        vector<T> cnt(C.size(), T{}); // cnt[i][j] is the maximum count of j-th color from the ancester nodes to node i.
        queue<int> q;
        for (int i = 0; i < C.size(); ++i) {
            if (indegree[i] == 0) { // if this node has 0 indegree, we can use it as a source node
                q.push(i);
                cnt[i][C[i] - 'a'] = 1; // the count of the current color should be 1
            }
        }
        int ans = 0, seen = 0;
        while (q.size()) {
            auto u = q.front();
            q.pop();
            int val = *max_element(begin(cnt[u]), end(cnt[u])); // we use the maximum of all the maximum color counts as the color value.
            ans = max(ans, val);
            ++seen;
            for (int v : G[u]) {
                for (int i = 0; i < 26; ++i) {
                    cnt[v][i] = max(cnt[v][i], cnt[u][i] + (i == C[v] - 'a')); // try to use node `u` to update all the color counts of node `v`.
                }
                if (--indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        return seen < C.size() ? -1 : ans;
    }
};



/*

https://leetcode.com/problems/largest-color-value-in-a-directed-graph/discuss/1198658/C%2B%2B-Topological-Sort

class Solution {
public:
    
    int helperDFS(string& colors, map<int, vector<int>>& edgeDict, 
                  set<int>& pathSet, map<char, int>& colorOrderIndex, 
                  vector<pair<int, char>>& colorNum, 
                  int *resultptr, int currNode, int debuglevel)
    {
        // if edgeDict contains the next node: 
        // for loop the next node in "edgeDict"
        //      add into "pathSet", check cycle, (return -1)
        //      update "colorOrderIndex", "colorNum"
        //      ret = DFS(); with updated currNode
        //      delete from "pathSet"
        //      update "colorOrderIndex", "colorNum"
        // else currNode is an end node: 
        //      check result with "colorNum[0]"
        // return 0
        
        vector<int>& edges = edgeDict[currNode]; 
        if(edges.size() > 0){
            for(int i = 0; i < edges.size(); i++){
                int nextNode = edges[i]; 
                
                // cycle check
                if(pathSet.find(nextNode) != pathSet.end()) return -1; 
                pathSet.insert(nextNode); 
                
                char colorNode = colors[nextNode]; 
                if(colorOrderIndex.find(colorNode) == colorOrderIndex.end()){
                    // append at the end. 
                    colorOrderIndex[colorNode] = colorNum.size(); 
                    pair<int, char> tmp = make_pair(1, colorNode); 
                    colorNum.push_back(tmp); 
                }
                else{
                    // update both colorOrderIndex and colorNum
                    int nextIndex = colorOrderIndex[colorNode]; 
                    pair<int, char>& nextPair = colorNum[nextIndex]; 
                    nextPair.first++; 
                    
                    while(nextIndex > 0){
                        // a possible swap. 
                        int tmpIndex = nextIndex - 1; 
                        // if the one ahead is >= after update, break
                        if(colorNum[tmpIndex].first >= nextPair.first) break; 
                        
                        // swap. 
                        int colorTmp = colorNum[tmpIndex].second; 
                        colorOrderIndex[colorTmp]++; // move back
                        colorOrderIndex[colorNode]--; // move ahead
                        pair<int, char> tmpPair = colorNum[tmpIndex]; 
                        colorNum[tmpIndex] = colorNum[nextIndex]; 
                        colorNum[nextIndex] = tmpPair; 
                        nextIndex--; 
                    }
                }
                
                for(int ii = 0; ii < debuglevel; ii++) cout << "  "; 
                cout << nextNode << endl; 
                
                
                int ret = helperDFS(colors, edgeDict, pathSet, colorOrderIndex, colorNum, resultptr, nextNode, debuglevel+1); 
                if(ret == -1) return -1; 
                
                // post-process
                pathSet.erase(nextNode); 
                // update colorOrderIndex and colorNum
                int nextIndex = colorOrderIndex[colorNode]; 
                pair<int, char>& nextPair = colorNum[nextIndex]; 
                nextPair.first--; 
                
                if(nextPair.first == 0){
                    colorOrderIndex.erase(colorNode); 
                    if(nextIndex != (colorNum.size() - 1)){
                        colorNum[nextIndex] = colorNum[colorNum.size() - 1]; 
                    }
                    colorNum.pop_back(); 
                }
                else{
                    while(nextIndex < (colorNum.size() - 1)){
                        // a possible swap. 
                        int tmpIndex = nextIndex + 1; 
                        // if the one ahead is <= after update, break
                        if(colorNum[tmpIndex].first <= nextPair.first) break; 
                        
                        // swap. 
                        int colorTmp = colorNum[tmpIndex].second; 
                        colorOrderIndex[colorTmp]--; // move ahead
                        colorOrderIndex[colorNode]++; // move back
                        pair<int, char> tmpPair = colorNum[tmpIndex]; 
                        colorNum[tmpIndex] = colorNum[nextIndex]; 
                        colorNum[nextIndex] = tmpPair; 
                        nextIndex++; 
                    }
                }
                
            }
        }
        else{
            // we are the end node. 
            *resultptr = ((*resultptr) < colorNum[0].first) ? colorNum[0].first : (*resultptr); 
        }
        
        return 0; 
    }
    
    
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        
        // v(path) >= v(subpath)
        // DFS + map: 
        //      DFS: keep searching until the end, avoid cycle. 
        //      map: histogram the color, when reach the end, check result. 
        
        map<int, vector<int>> edgeDict; // edge dictionary for checking
        set<int> sourceSet; // source/starting point set
        
        for(int i = 0; i < colors.size(); i++){
            sourceSet.insert(i); 
        }
        for(int i = 0; i < edges.size(); i++){
            int start = edges[i][0]; 
            int end = edges[i][1]; 
            
            // a source node should not be as an end. 
            auto it = sourceSet.find(end); 
            if(it != sourceSet.end()) sourceSet.erase(it); 
            
            // add into the dictionary
            if(edgeDict.find(start) == edgeDict.end()){
                vector<int> tmp; 
                tmp.push_back(end); 
                edgeDict[start] = tmp; 
            }
            else{
                edgeDict[start].push_back(end); 
            }
        }
        
        if(sourceSet.size() == 0) return -1; // no source, we are a big cycle
        
        // start algorithm. 
        set<int> pathSet; // track which node is on the path
        int result = 0; 
        map<char, int> colorOrderIndex; // use to index the colorNum
        vector<pair<int, char>> colorNum; // record the number of each color, occurrence decreasing order
        
        for(auto it = sourceSet.begin(); it != sourceSet.end(); it++){
            int sourceNode = *it; 
            
            // pathSet, colorOrderIndex, colorNum should be empty here. 
            // initialize
            pathSet.insert(sourceNode); 
            char colorNode = colors[sourceNode]; 
            colorOrderIndex[colorNode] = 0; // the first one in the colorNum
            pair<int, char> tmp = make_pair(1, colorNode); 
            colorNum.push_back(tmp); 
            
            // DFS this node, update the result. 
            cout << sourceNode << endl; 
            int ret = helperDFS(colors, edgeDict, pathSet, colorOrderIndex, colorNum, &result, sourceNode, 1); 
            
            if(ret == -1) return ret; // find cycle
            
            pathSet.erase(sourceNode); 
            colorOrderIndex.erase(colorNode); 
            colorNum.clear(); 
        }
        
        return result; 
    }
};

*/
