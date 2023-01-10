class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // use solution pq answer. 

        int i = 0, res;
        int cur = startFuel; 
        priority_queue<int>pq;
        for (res = 0; cur < target; res++) {
            while (i < stations.size() && stations[i][0] <= cur)
                pq.push(stations[i++][1]);
            if (pq.empty()) return -1;
            cur += pq.top(), pq.pop();
        }
        return res;


    }
};

/*

// ahh.. quite close to the correct answer.. 

    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        // if we stand at position i (miles), with fuel remaining. 
        // we can reach [i, i+fuel] range
        //      if covers target, return 0. 
        // we check all stations in between, station: pos, delta
        //      if no station, return -1
        // we check the outcome if we fill at them: 
        //      (fuel - (pos - i)) + delta
        // we can reach: 
        //      pos + (fuel - (pos - i)) + delta = i + fuel + delta
        // we greedy choose the largest one. 

        int pos = 0; // current position, "i"
        int currfuel = startFuel; 

        int ret = 0; // times to refuel
        int currstat = 0; // current station index
        bool currfilled = false; // station at "pos" is not refueled, init case e.g. station at mile 0. 
        while (1){
            cout << pos << ", reach: " << (pos + currfuel) << endl; 
            if ((pos + currfuel) >= target)
                return ret; 
            
            vector<int> stationindexes; 
            for (int i = currstat; i < stations.size(); i++){
                if (stations[i][0] == pos){
                    if (currfilled == false){
                        stationindexes.push_back(i); 
                    }
                    continue; 
                }
                if (stations[i][0] > pos){
                    if (stations[i][0] <= (pos + currfuel)){
                        stationindexes.push_back(i); 
                    }
                    else{
                        break; 
                    }
                }
                else{
                    // something wrong.. 
                    cout << "Error.. " << endl; 
                }
            }
            if (stationindexes.size() == 0){
                return -1; // no more stations... 
            }

            int nextpos, nextfuel; 
            int dist = pos + currfuel; 
            for (int i : stationindexes){
                int currdist = pos + currfuel + stations[i][1]; 
                if (currdist > dist){ // we take the earlier one, no equal
                    dist = currdist; 
                    nextpos = stations[i][0]; 
                    nextfuel = (currfuel - (nextpos - pos)) + stations[i][1]; 
                    currstat = i; // update currstat!! 
                }
            }   
            currfilled = true; // always. 

            ret++; // complete 1 refuel. 
            pos = nextpos; 
            currfuel = nextfuel; 
        }

        // never reach here.. 
        return -1; 
    }

*/
