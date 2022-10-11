class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size(), res = 0, sum = 0;
        sum = accumulate(nums.begin(), nums.end(),0);
        
        int N = n/2;
        vector<vector<int>> left(N+1), right(N+1);
        
		//storing all possible sum in left and right part
        for(int mask = 0; mask<(1<<N); ++mask){
            int sz = 0, l = 0, r = 0;
            for(int i=0; i<N; ++i){
                if(mask&(1<<i)){
                    sz++;
                    l += nums[i];
                    r += nums[i+N];
                }
            }
            left[sz].push_back(l);
            right[sz].push_back(r);
        }

        for(int sz=0; sz<=N; ++sz){
            sort(right[sz].begin(), right[sz].end());
        }

        res = min(abs(sum-2*left[N][0]), abs(sum-2*right[N][0]));

		//iterating over left part
        for(int sz=1; sz<N; ++sz){
            for(auto &a : left[sz]){
                int b = (sum - 2*a)/2, rsz = N-sz;
                auto &v = right[rsz];
                auto itr = lower_bound(v.begin(), v.end(),b); //binary search over right part
                
                if(itr!=v.end()) res = min(res, abs(sum-2*(a+(*itr))));
                if(itr!= v.begin()){
                    auto it = itr; --it;
                    res = min(res, abs(sum-2*(a+(*it))));
                }                
            }
        }
        return res;
        
    }
};

/*

// totally no idea about this algorithm... sad.. 

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        // some init ideas: 
        // sort the "nums", then the array will be: middle v.s. head+tail
        // 2 questions: 
        //    1. will it be contiguous in the middle part? 
        //    2. how to quickly determine the beginning of the middle, if Q1 is true. 
        
        // Q1: if there is a minimal split: middle v.s. head+tail, 
        //      can we find a swap to make it smaller? 
        //      if middle > (head+tail): swap middle[0] and head[end]? 
        //      head[0]..head[end] middle[0]..middle[end] tail[0]..tail[end] => compare
        //      head[0].. middle[0] head[end] ..middle[end] tail[0]..tail[end] v.s.
        //      head[0].. head[end]middle[0].. middle[end]tail[0]..tail[end]
        //      s(m) : s(h)+s(t) compare: 
        //      s(m) - middle[0] + head[end] : s(h)+s(t) + middle[0] - head[end]
        //      s(m) - middle[end] + head[end] : s(h)+s(t) + middle[end] - head[end]
        
        // Q1 is not true, then how to make the algorithm? 
        
        
        
        
    }
};

*/
