
// this is not hard.. merge intervals will be it. 
// sort by start, 
// hmmmmm no.. check multiset std!! 

class Solution {
public:
	vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		vector<pair<int,int>> cnt;

		for(auto& x:buildings)
		{
			int left=x[0];
			int right=x[1];
			int height=x[2];
			cnt.push_back({left,height});
			cnt.push_back({right,-height});

		}

		auto comp=[&](pair<int,int>& a, pair<int,int>& b)
		{
			if(a.first!=b.first)
			{
				return a.first<b.first;
			}
			else
			{
				return a.second>b.second;
			}
		};

		sort(cnt.begin(),cnt.end(),comp);

		multiset<int> Set;
		vector<vector<int>> ans;

		for(int i=0;i<cnt.size();i++)
		{
			int cur=cnt[i].first;
			int height=cnt[i].second;
			bool enter=height>=0;
			height=abs(height);

			if(enter)
			{
				if(Set.empty() || height>*Set.rbegin())
				{
					ans.push_back({cur,height});
				}

				Set.insert(height);
			}
			else if(!enter)
			{
				Set.erase(Set.find(height));
				if(!Set.empty() && height>*Set.rbegin())
				{
					ans.push_back({cur,*Set.rbegin()});
				}
				if(Set.empty())
				{
					ans.push_back({cur,0});
				}
			}
		}

		return ans;
	}
};
