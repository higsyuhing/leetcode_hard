
class Solution {
public:
    int minPatches(vector<int>& nums, int n) {
        long miss = 1, added = 0, i = 0;
        while (miss <= n) {
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i++];
            } else {
                miss += miss;
                added++;
            }
        }
        return added;
    }
};


/*
// get part of it.. but not there..... 


class Solution {
public:
    void init_havingset(vector<int>& nums, set<int>& havingset, int i, int curr){
        if (i == nums.size()) return; 
        
        // we don't add the current: 
        init_havingset(nums, havingset, i+1, curr); 

        // we add the current: 
        curr += nums[i]; 
        havingset.insert(curr); 
        init_havingset(nums, havingset, i+1, curr); 
    }

    void printset(set<int>& oneset){
        for (auto it = oneset.begin(); it != oneset.end(); it++)
            cout << " " << *it; 
        cout << endl; 
    }

    int minPatches(vector<int>& nums, int n) {
        // keep a having set and a missing set
        // for the smallest value in the missing set, 
        //  adding any larger values will not help. 
        // e.g. in case [1, 5, 10], n = 20
        //  having={1,5,6,10,11,15}, then 2 will be the first to add
        //  having={1,2,3,5,6,7,8,10,11,12,13,15,17}, then 4 will the next to add

        // missing set is too costly.. we need a better missing set: 
        // missing set will have largest value: max{havingset}+1
        // break if the next target > n

        // use set b.c. we need to know the max/min value
        set<int> havingset; 
        set<int> missingset; 

        init_havingset(nums, havingset, 0, 0); 
        long currmax = *(havingset.rbegin()); 
        for (int i = 1; i <= (currmax+1); i++){
            if (havingset.count(i) == 0)
                missingset.insert(i); 
        }

        long nextmax, target, ret; 
        bool fastflag = false; // <-- optimization 3
        ret = 0; 
        while (1){
            // cout << "loop begin\n"; 
            // printset(havingset); 
            // printset(missingset); 

            if (fastflag == false)
                target = *(missingset.begin()); 
            else{ // <-- optimization 3
                // target == (currmax + 1)
                currmax = currmax + target; 
                target = currmax + 1; 
                ret++; 
                if (target > n) break; 
                continue; 
            }
            if (target > n) break; 
            if (target == (currmax + 1)){
                fastflag = true; 
                continue; 
            }
            missingset.erase(target); 
            for (int i = 1; i < target; i++) // optimization 2
                havingset.erase(i); 
            ret++; 

            // makeup missing set
            for (int i = (currmax+2); i <= (currmax+target+1); i++){
                if (havingset.count(i) == 0)
                    missingset.insert(i); 
            }

            // cout << "target: " << target << endl; 
            // printset(missingset); 

            // check all elements in missingset: // optimization 1
            // is (missingset[i] - target) in the havingset. 
            vector<int> tmp; 
            for (auto it = missingset.begin(); it != missingset.end(); it++){
                int curr = *it; 
                if (((curr - target) < target) || havingset.count(curr - target) != 0){ // we have, new add. 
                    tmp.push_back(curr); 
                }
            }
            for (int i = 0; i < tmp.size(); i++){
                missingset.erase(tmp[i]); 
                havingset.insert(tmp[i]); 
            }
            havingset.insert(target); 

            // compute the next max.. makesure it exists a value in missingset
            nextmax = *(havingset.rbegin()); 
            for (int i = currmax+target+2; i <= (nextmax+1); i++){ // may no add
                if (havingset.count(i) == 0)
                    missingset.insert(i); 
            }
            currmax = nextmax; 
        }

        return ret; 
    }
};


*/
