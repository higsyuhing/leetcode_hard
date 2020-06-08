class Solution {
public:
    vector<int> parent;
    vector<int> rank;
    int find(int x)
    {
        return parent[x]==-1 || parent[x]==x?x:find(parent[x]);
    }
    int numSimilarGroups(vector<string>& a) {
        parent=vector<int>(a.size(),-1);
        rank=vector<int>(a.size(),0);
        for(int i=0;i<a.size();i++)
        {
            for(int j=i+1;j<a.size();j++)
            {
                int c=0;
                for(int k=0;k<a[i].size();k++)
                {
                    if(a[i][k]!=a[j][k] && ++c>2)
                        break;
                    
                }
                if(c<=2)
                {
                    int x=find(i),y=find(j);
                    if(x!=y)
                    {
                        if(rank[x]>rank[y])
                        {parent[y]=x;rank[x]++;}
                        else
                        {parent[x]=y;rank[y]++;}
                    }
                }
            }
        }
        int ans=0;
        for(int i=0;i<a.size();i++)
            if(find(i)==i)
                ans++;
        return ans;
    }
};
