class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 2 non-overlap sub arrays has max "go up". 
        // accept hint: DP. 
        // kadane's algo with a previous session high. 
        int prevhigh = 0; 
        int prevtmp = 0; 
        int local_max = 0; 
        int global_max = INT_MIN; 
        for (int i = 1; i < prices.size(); i++){
            int inc = prices[i] - prices[i-1]; 

            if (inc < 0 && local_max > prevtmp){ // if fall, make a record for this session
                prevtmp = local_max; 
            }
            // local_max = max(inc, inc + local_max); 
            if (inc >= (inc + local_max)){ // start a new session
                local_max = inc; 
                prevhigh = (prevhigh < prevtmp) ? prevtmp : prevhigh; 
                prevtmp = 0; 
            }
            else{
                local_max += inc; 
            }

            global_max = (global_max < local_max) ? local_max : global_max; 
        }

        return 0; 
    }
};

/*
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/solutions/135704/detail-explanation-of-dp-solution/?orderBy=most_votes
*/
