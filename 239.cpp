class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // hash + pq
        // a maximum pq to keep the max value of the window
        // if window moves, add the moved num into hash (if multiple, add 1)
        // when compute the max of the window, 
        //      check if top() is in hash, if so, pop and hash--
        //      else add this value into array
        
        map<int, int> hashmap; 
        priority_queue<int> windowqueue; 
        vector<int> res; 
        
        // init stage
        for(int i = 0; i < k; i++){
            windowqueue.push(nums[i]); 
        }
        res.push_back(windowqueue.top()); 
        
        for(int i = 0; i < (nums.size()-k); i++){
            // add into hash
            if(hashmap.find(nums[i]) == hashmap.end()){
                hashmap[nums[i]] = 1; 
            }
            else hashmap[nums[i]]++; 
            
            windowqueue.push(nums[i+k]); 
            int topval; 
            while(1){
                topval = windowqueue.top(); 
                if(hashmap.find(topval) == hashmap.end()) break; 
                windowqueue.pop(); 
                hashmap[topval]--; 
                if(hashmap[topval] == 0) hashmap.erase(topval); 
            }
            
            res.push_back(topval); 
        }
        
        return res; 
        
    }
};


/*
// smart.. 

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int sz = nums.size();
        std::deque<int> dq;
        
        vector<int> ans;
        for (int i = 0; i < sz; ++i) {
            int cur = nums[i];
            while (!dq.empty() && cur >= nums[dq.back()]) dq.pop_back();
            dq.push_back(i);
            
            if (dq.front() < i+1-k) dq.pop_front();
            
            if (i >= k-1) ans.push_back(nums[dq.front()]);
        }
        return ans;
    }


*/
