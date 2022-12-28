class Solution {
public:

    int helper1(map<int, int>& hash, vector<vector<int>>& edges){
        // cycle through the root, in this case, with any start point, have a cycle
        // cycle detection, then choose the one with largest index on the cycle.. 
        vector<bool> visited(edges.size(), false); 

        int curr = 1; // start from node 1
        while (visited[curr-1] == false){
            visited[curr-1] = true; 
            curr = edges[hash[curr]][0]; // go parent
        }
        // now the curr is one of the cycle node.. cycle it again
        int start = curr; 
        int index = hash[curr]; 
        curr = edges[hash[curr]][0]; 
        while (start != curr){
            index = (index < hash[curr]) ? hash[curr] : index; 
            curr = edges[hash[curr]][0]; 
        }

        return index; 
    }

    // detect if there is a cycle starting from edge index
    // assume index not included in hash
    bool cycledetection(map<int, int>& hash, vector<vector<int>>& edges, int index){
        vector<bool> visited(edges.size(), false); 
        int start = edges[index][1]; 
        visited[start-1] = true; 
        int curr = edges[index][0]; 

        while (visited[curr-1] == false){
            visited[curr-1] = true; 
            if (hash.find(curr) == hash.end()){
                return false; 
            }
            curr = edges[hash[curr]][0]; // go parent
        }
        return true; 
    }


    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // either 1) cycle, or 2) 2 parents
        // maintain a hashmap for map[curr] = edge index
        // if we meet conflict, also no cycle, return the current edge record (last)
        // else we perform a cycle detection, select the last edge index
        // see later comments for better explanation.... 

        map<int, int> hash; 
        int pindex = -1; 
        for (int i = 0; i < edges.size(); i++){
            int v = edges[i][1]; 
            if (hash.find(v) == hash.end()){
                hash[v] = i; 
            }
            else{
                if (pindex != -1){
                    cout << "Error case.. " << endl; 
                    vector<int> ret; 
                    return ret; 
                }
                pindex = i; 
            }
        }

        // 2 cases: 
        // no pindex: cycle through the root.. 
        //      cycle detection, and erase the largest index edge
        // have pindex: 
        //   have 2 edge candidates: pindex and hash[edges[pindex][1]]
        //      cycle detection for both.. 
        //      case 1: 1 have cycle, 1 have not, choose the one has a cycle
        //      case 2: both no cycle, erase the larger index one (pindex)

        if (pindex == -1){
            int retindex = helper1(hash, edges); 
            return edges[retindex]; 
        }

        if (cycledetection(hash, edges, pindex) == true){
            return edges[pindex]; 
        }
        int indexalt = hash[edges[pindex][1]]; 
        if (cycledetection(hash, edges, indexalt) == true){
            return edges[indexalt]; 
        }

        // pindex = (pindex < indexalt) ? indexalt : pindex; 
        return edges[pindex]; 
    }
};

// the solution uses union-find.. idk why is that.. but anyway... 
