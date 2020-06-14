class Solution {
    bool bs(vector<int>&nums, long long mid, long long n,int m)
    {
        long long sum=0;
        int cnt=0;
        for(int i=0;i<n;i++)
        {
            if(nums[i]>mid)
                return false;
            sum+=nums[i];
            if(sum>mid)
            {
                sum = nums[i];
                cnt++;
            }
        }
        cnt++;
        if(cnt<=m)
            return true;
        return false;
    }
public:
    int splitArray(vector<int>& nums, int m) {
        long long sum=0, n= nums.size();
        for(auto it: nums)
            sum+=it;
        long long lo=1,hi = sum;
        int ans;
        while(lo<=hi)
        {
            long long mid = lo+(hi-lo)/2;
            if(bs(nums,mid,n,m))
            {
                ans =mid;
                hi = mid-1;
            }
            else
                lo = mid+1;
        }
        
        return ans;
    }
};


/*
I don't even understand the explanation of this solution.. 
but look at the code, it's not that hard to understand.. 

- At first we will calculate the total sum of the elements.
- We will binary search from 1 to sum in order to find the minimum sum that satisfies the result.
- For every mid value we will count the number of contigeous subarrays which have the subarray sum <= mid.
- remember, we cannot split the array less than count times to get mid as minized subarray sum.
- if count greater than m, then we must need to split the array at least count times to get mid as maximum sum and we cannot do it as the upper bound of spliting is m. in this case we cannot split the array less count times.
- if count is less than or equal to m then it satiesfies the condition. remeber we can split the the array into more than count parts, but not less than the counts parts.

*/
