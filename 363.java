/**
* Idea: 
*  We scan all columns and for each group of columns we calculate the row sum of till that columns  
*  Say we have 3 columns, so we will have group of column such that [0]. [0,1], [0,1,2], [1], [1,2], [2]
*  then we calculate corresponding row sum this is where we use rolling sum to reduce complexity
* 
*  Then we use the row sum array to get the maximum contiguous sub array sum which is under k
*  For this we can use kadane's algorithm 
*   Say we have [1, 3, -1, 2]
*   Good explanation of Kadane's Algorithm https://www.youtube.com/watch?v=2MmGzdiKR9Y
*
*   Kadane's algorith states that we can figure out maximum contiguas subarray sum with only one scan of the array
*   The basic idea is every element can be the max or the max can come from elements previous to that element
*
*   In the above example take the first element (1), the max subarray sum is 1 till that point
*   For second element, the choice is between use the element 3 or (3 and previous subarray sum) in this case max(3, 4) = 4
*   For third element (-1), the choice is -1 or previous 4 -> (4 + -1) = 3 the output is  3
*   For fourth element (2), the choice is 2 or previous 3 -> (3 + 2) = 5, the output is 5 
*   Looks like the maximum subarray sum here is the summation of the complete array. Otherwise we would've take max of all above 
*   values MAX(1, 4, 3, 5 ) => 5
*   
*   This is a bit special case where we need to find the sum does not exceed k value , say k is 2
*   The trick is to maintain a sorted order of the sums found at each step, so the array will look like 
*   [We add a 0 for convinience with negative value, meaning our value should not go negative]
*   (0) the first element is having sum 1, then (1 - 2) = -1, the closest ceiling value is 0, we can subtract 0 to not exceed max value 2, and the closest value we can get to 2 is (1 - 0) = 1
*   (0, 1) THe second sum is 4, the closest larger value of 4 - 2 = 2 is not found, so we just add it, meaning till now we can't subtract anything from 4 which will make sure it won't exceed 2
*   (0, 1, 4) the third sum is 3, the closest larger value of 3 - 2 = 1, thus we know we can go till (3 - 1) = 2, this is the closest of 2 we go. This can be inferred as if we take (3, -1) that is the closest sum of 2. 
*  (0, 1, 3, 4) the next value is 5, thus (5 - 2) = 3, closest to 3 is 3, thus we again know we can go till (5 - 3) = 2, the corresponding subarray will be same one as above.
*   Time Complexity => if n is no of cols and m is no of rows, then O(n^2 * mlogm)
*   Space Complexity => O(m) (originally 2m)
*/

class Solution {
    public int maxSumSubmatrix(int[][] matrix, int k) {
        
        int maxSum = Integer.MIN_VALUE;
        int rows = matrix.length;
        int cols = matrix[0].length;
        for (int i = 0; i < cols; i++) {
            
            // Starting at each column we incrementally go till end
            // [0], [0,1], [0,1,2]
            // [1], [1,2]
            // [2]
            
            int[] rowSum = new int[rows];
            for (int col = i; col < cols; col++) {
                for (int row = 0; row < rows; row++) {
                    rowSum[row] += matrix[row][col];
                }
                
                // We have calculated the row sum till the current column
                // Now it is time to mind the max subarray sum we can achieve lesser than k
                int maxSumUnderK = maxSubarrayLessThanK(rowSum, k);
                maxSum = Math.max(maxSum, maxSumUnderK);
                
                // This will prune the computations a bit, if we achieve k, we know 
                // we don't need to go futher this the max we can go, return now, don't waste time computing more
                if (maxSum == k) return k;
            }
        }
        return maxSum;
    }
    
    // This is Kadane's algorithm .. a bit modified
    private int maxSubarrayLessThanK(int[] array, int k) {
        int maxSumUnderK = Integer.MIN_VALUE;
        
        // Best possible data structure to keep stuff in sorted order and get back in log n time
        TreeSet<Integer> sortedPreviousSums = new TreeSet<>();
        sortedPreviousSums.add(0);
        
        int incrementalSum = 0;
        for (int i = 0; i < array.length; i++) {
            incrementalSum += array[i];
            
            // Now we try to find if our sorted sum list is having
            // any thing just larger than (sum - k), say that is previousSum
            // If there is an element we know we can go close to k as much as (sum - previousSum)
            Integer previousSum = sortedPreviousSums.ceiling(incrementalSum - k);
            if (previousSum != null) {
                maxSumUnderK = Math.max(maxSumUnderK, incrementalSum - previousSum);
            }
            
            sortedPreviousSums.add(incrementalSum);
        }
        
        return maxSumUnderK;
    }
}


/*
// cpp solution.. 
class Solution {
public:
    
    int maxSumLimitK(vector<int> &v, int k){
        
        int ans = INT_MIN;
        int currSum = 0;
        set<int> st;
        st.insert(0);
        
        for(int i = 0; i < v.size(); i++){
            currSum += v[i];
            auto pos =  st.lower_bound(currSum - k);
            if(pos != st.end()) ans = max(ans, currSum - *pos);
            st.insert(currSum);
        }
        
        return ans;
        
    }
    
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        
        if(matrix.empty()) return 0;
        
        int n = matrix.size();
        int m = matrix[0].size();
        int maxSum = INT_MIN;
        
        for(int L = 0; L < m; L++){
            vector<int> sum(n, 0);
            for(int R = L; R < m; R++){
                for(int i = 0; i < n; i++) sum[i] += matrix[i][R];
                int currMax = maxSumLimitK(sum, k);
                maxSum = max(maxSum, currMax);
            }
        }
        
        return maxSum;
        
    }
};


*/
