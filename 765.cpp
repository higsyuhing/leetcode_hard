class Solution {
public:
    int search(vector<int> row, int num, int i, int j)
    {
        for(int k=i; k<=j; k++)
        {
            if(row[k]==num)
                return k;
        }
        return -1;
    }
    
    
    int minSwapsCouples(vector<int>& row) 
    {
        int ans=0, i=0, j;
        int n = row.size();
        
        while(i<n)
        {
            if(row[i]%2==0)
            {
                if(row[i+1]==row[i]+1)
                    i = i+2;
                else
                {
                    j = search(row,row[i]+1,i+2,n-1);
                    swap(row[i+1],row[j]);
                    ans++;
                    i=i+2;
                }
            }
            else
            {
                if(row[i+1]==row[i]-1)
                    i = i+2;
                else
                {
                    j = search(row,row[i]-1,i+2,n-1);
                    swap(row[i+1],row[j]);
                    ans++;
                    i=i+2;
                }
            }
        }
        return ans;
    }
};
