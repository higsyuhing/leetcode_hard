class Solution {
public:
    
    struct s_GraphNode{
        string word; 
        vector<struct s_GraphNode *> neighbors; 
        int degree; // for BFS: -1, init; >0, path node, -2 endWord, 0 beginWord. 
    }; 
    typedef struct s_GraphNode GraphNode; 
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ret; 
        int wordlen = beginWord.size(); 
        
        // construct a map and graph attribute nodes
        // it takes N^2 since we need to compare each other for the connection.. 
        map<string, GraphNode*> dict; 
        for (string& word : wordList){
            GraphNode* curr = new GraphNode(); 
            curr->word = word; 
            curr->degree = -1; 
            dict[word] = curr; 
        }
        
        // if endWord not in the map, exit. 
        // some deconstruction here.. 
        if (dict.count(endWord) == 0) return ret; 
        dict[endWord]->degree = -2; 
        
        if (wordList.size() > 1){
            for (int i = 0; i < (wordList.size() - 1); i++){
                for (int j = i+1; j < wordList.size(); j++){
                    int diffchar = 0; 
                    string& wordi = wordList[i]; 
                    string& wordj = wordList[j]; 
                    for (int k = 0 ; k < wordlen; k++){
                        if (wordi[k] != wordj[k]){
                            diffchar++; 
                            if (diffchar > 1) break; 
                        }
                    }
                    
                    if (diffchar == 1){
                        // 2 words are connected in graph. 
                        GraphNode *nodei, *nodej; 
                        nodei = dict[wordi]; 
                        nodej = dict[wordj]; 
                        nodei->neighbors.push_back(nodej); 
                        nodej->neighbors.push_back(nodei); 
                    }
                }
            }
        }
        // add beginWord into the graph.. 
        bool flagbegininList = (dict.count(beginWord) > 0); 
        if (flagbegininList == false){
            GraphNode* curr = new GraphNode(); 
            curr->word = beginWord; 
            curr->degree = 0; 
            dict[beginWord] = curr; 
            
            for (int i = 0; i < wordList.size(); i++){
                int diffchar = 0; 
                string& wordi = wordList[i]; 
                for (int k = 0 ; k < wordlen; k++){
                    if (wordi[k] != beginWord[k]){
                        diffchar++; 
                        if (diffchar > 1) break; 
                    }
                }
                if (diffchar == 1){
                    // 2 words are connected in graph. 
                    GraphNode *nodei; 
                    nodei = dict[wordi]; 
                    nodei->neighbors.push_back(curr); 
                    curr->neighbors.push_back(nodei); 
                }
            }
        }
        else{
            dict[beginWord]->degree = 0; 
        }
        
        
        // now here we come to a BFS.. 
        // the problem is, we need to print all paths out.. 
        //      use degree to backtrack. 
        //      i.e. when reach the endWord, we backtrack through nodes. 
        //      looking for degree decreasement.. 
        // BFS for searching, DFS for path construction.. 
        
        // step 1, BFS search for the endWord
        // it's possible that the graph is not connected as a whole, then
        //      the queue will be empty but not reached yet. 
        queue<GraphNode*> bfsqueue; 
        bool flagEnd = false; 
        
        bfsqueue.push(dict[beginWord]); 
        while (!bfsqueue.empty()){
            GraphNode* curr = bfsqueue.front(); 
            bfsqueue.pop(); 
            int depth = curr->degree; 
            
            for (GraphNode* next : curr->neighbors){
                if (next->degree >= 0) continue; // we visit before
                if (next->degree == -2){
                    flagEnd = true; // curr is a neighbor of endWord
                    next->degree = depth+1; 
                    // use this to backtrack all endWord's neighbors with
                    // "depth-1" (i.e. depth here) degree
                    break; 
                    // we can label the endWord's depth. no need for others
                    // i.e. all current nodes in bfsqueue have at least degree depth
                    // all degree=depth nodes are found already. then its ok to break
                }
                
                // -1
                next->degree = depth+1; 
                bfsqueue.push(next); 
            }
            
            if (flagEnd) break; 
        }
        
        if (flagEnd == false) return ret; // not connected graph, endWord not reachable. 
        
        //cout << dict[beginWord]->degree << "," << dict[endWord]->degree << endl; 
        
        // we found endWord, with it labeled. now backtrack with DFS
        GraphNode* curr = dict[endWord]; 
        int currdepth = curr->degree; 
        vector<GraphNode*> dfsstack(currdepth); // [currdepth, 1]
        int stackpos = 0; // end point, stack will be valid in [0, stackpos)
        
        funcDFS(curr, currdepth, dfsstack, stackpos, ret); 
        
        return ret; 
    }
    
    void funcDFS(GraphNode* curr, int currdepth, 
                 vector<GraphNode*>& dfsstack, int stackpos, vector<vector<string>>& ret){
        // find all curr's neighbors with degree currdepth-1, 
        //      until the beginWord (degree 0)
        
        // if we reach the beginWord, record it. 
        if (curr->degree == 0){
            vector<string> tmp; 
            tmp.push_back(curr->word); 
            for (int i = stackpos-1; i >= 0; i--){
                GraphNode* tmpnode = dfsstack[i]; 
                tmp.push_back(tmpnode->word); 
            }
            ret.push_back(tmp); 
            return; 
        }
        
        // curr->degree > 0
        // push curr node into the stack, then find all nodes with degree=depth-1
        dfsstack[stackpos] = curr; 
        stackpos++; 
        
        for (GraphNode* next : curr->neighbors){
            if (next->degree != (currdepth-1)) continue; 
            funcDFS(next, currdepth-1, dfsstack, stackpos, ret); 
        }
        
        stackpos--; // pop
    }
};


// wow.. can't imagine I can write this by my own (without checking any solution/discussion).. it takes me around 1 hour.. 
// and only wrong once, then find 1 bug and success! 


