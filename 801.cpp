class Solution {
public:

    int dpdfs(vector<int>& nums1, vector<int>& nums2, pair<int, int>& region){
        // for index l+i, use dp[i][0] for not swap, dp[i][1] for swap
        //      dp[i][0/1] means the minimum swap to achieve the goal in range [l,i]
        //      return min dp[r][0/1]
        int l = region.first; 
        int r = region.second; 

        // vector<int> dp0(r-l, -1); // dp0[index] not swap
        // vector<int> dp1(r-l, -1); // dp0[index] swap
        // dp0[0] = 0; dp1[0] = 1; 
        // opt: we dont need an vector
        int dp0 = 0; 
        int dp1 = 1; 

        for (int i = 1; i < (r-l); i++){
            int curr = l + i; 
            // 4 case: 00, 01, 10, 11
            int c00, c01, c10, c11; 
            c00 = INT_MAX; c01 = INT_MAX; c10 = INT_MAX; c11 = INT_MAX; 
            if (nums1[curr-1] < nums1[curr] && nums2[curr-1] < nums2[curr]){
                c00 = dp0; 
                c11 = dp1 + 1; 
            }
            if (nums1[curr-1] < nums2[curr] && nums2[curr-1] < nums1[curr]){
                c01 = dp0 + 1; 
                c10 = dp1; 
            }
            dp0 = (c00 > c10) ? c10 : c00; 
            dp1 = (c11 > c01) ? c01 : c11; 
        }

        return (dp0 > dp1) ? dp1 : dp0; 
    }

    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        // for index i-1, i, i+1
        // if max[i-1] < any[i] < min[i+1], then we say index i separate the array
        //      and swap it or not at index i does not matter
        // then we cut the array into regions.. 
        // for each region [l, r], we dfs search swap or not on each pair. 
        // for index l+i, use dp[i][0] for not swap, dp[i][1] for swap
        //      dp[i][0/1] means the minimum swap to achieve the goal in range [l,i]
        //      return min dp[r][0/1]
        // then we put all regions together

        int start = -1; 
        vector<pair<int, int>> regions; // [l, r)
        int len = nums1.size(); 
        for (int i = 1; i < len; i++){
            int maxl = (nums1[i-1] > nums2[i-1]) ? nums1[i-1] : nums2[i-1]; 
            int minc = (nums1[i] > nums2[i]) ? nums2[i] : nums1[i]; 
            if (maxl < minc){
                if (start != -1){ // we reach a region end
                    // need to work until pair i-1, but not i
                    regions.push_back(make_pair(start, i)); 
                    start = -1; 
                }
                // if start == -1, do nothing
            }
            else{
                if (start == -1){
                    // work on pair i-1, that is the first one.. 
                    start = i-1; 
                }
                // if start != -1, do nothing
            }
        }
        if (start != -1){
            regions.push_back(make_pair(start, len)); // the end is a one.. 
        }

        int ret = 0; 
        for (auto& region : regions){
            // cout << region.first << ", " << region.second << endl; 
            ret += dpdfs(nums1, nums2, region); 
        }

        return ret; 
    }
};
