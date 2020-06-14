class Solution {
private:    
    struct Job {
        int startT, endT, profit;
        Job(int s, int e, int p):startT(s), endT(e), profit(p){}
        bool operator< (const Job& j) { return endT < j.endT; } // sorted by endT
    };    
    
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) 
    {        
        vector<Job> jobs;
        for (int i = 0; i < profit.size(); i++)
            jobs.emplace_back(startTime[i], endTime[i], profit[i]);
        sort(jobs.begin(), jobs.end()); // sort by endT
        
        map<int, int> maxProfit = {{0,0}}; // dp[endTime]: max profit if end at endTime        
        for (auto& job : jobs) {
            auto it = --maxProfit.upper_bound(job.startT); // position of latest endTime not overlapping job
            int curProfit = job.profit + it->second; // max profix if taking current job
            int preProfix = maxProfit.rbegin()->second; // max profix if not taking current job
            if (curProfit > preProfix)
                maxProfit[job.endT] = curProfit;
        }
        return maxProfit.rbegin()->second;
    }
};

// ... reminds me of adv algo class.. 
