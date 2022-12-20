class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<int> dp(target + 1, -10000);
        dp[0] = 0;
        for (int t = 1; t <= target; ++t) {
            for (int i = 0; i < 9; ++i) {
                dp[t] = max(dp[t], t >= cost[i] ? 1 + dp[t - cost[i]] : -10000);
            }
        }
        if (dp[target] < 0) return "0";
        
        string res = "";
        for (int i = 8; i >= 0; --i) {
            while (target >= cost[i] && dp[target] == dp[target - cost[i]] + 1) {
                res.push_back('1' + i);
                target -= cost[i];
            }
        }
        return res;
    }
};


/*
struct less_than_key
{
    inline bool operator() (const pair<int, int>& p1, const pair<int, int>& p2)
    {
        if (p1.first != p2.first){
            return (p1.first < p2.first); // smaller cost always
        }
        else{
            return (p1.second >= p2.second); // if same cost, larger number first
        }
    }
};

class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        // decompose question: given the cost, we should find the set of numbers: 
        // xi, i from 0-8, sum of xi*cost[i] == target
        // then try to maximize sum of xi
        // also if we cannot found solution, return empty str.. 

        vector<pair<int, int>> scost(9, make_pair(0,0)); 
        for (int i = 0; i < 9; i++){
            int curr = cost[i]; 
            scost[i].first = curr; 
            scost[i].second = i+1; 
        }
        sort(scost.begin(), scost.end(), less_than_key()); 

        // debug check; OK, pass. 
        // for (int i = 0; i < 9; i++){
        //     cout << scost[i].first << ", " << scost[i].second << endl; 
        // }

        // a greedy solution: 
        // if we use more digit, then take it
        // else we try to use the next one.. 
        int sol[9] = {0}; // sol variable in scost

        // give it up.. updated with solution in discussion

        return ""; 
    }
};


*/
