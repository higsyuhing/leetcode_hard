class Solution {
public:
    vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
        unordered_map<int,int> Map;
		for(auto& word:words)
		{
			int mask=0;
			for(auto& ch:word)
			{
				mask|= (1<<(ch-'a'));
			}

			Map[mask]+=1;
		}

		vector<int> ans;
		for(auto& puzzle:puzzles)
		{

			int len=puzzle.size()-1;

			int count=0;
			for(int i=0;i<(1<<len);i++)
			{
				 int mask = (1<<(puzzle[0]-'a'));
					for(int j=0;j<len;j++)
					{
						if((i & (1<<j)))
						{
							mask|= (1<<(puzzle[j+1]-'a'));
						}

					}

					if(Map.count(mask))
					{
						count+=Map[mask];
					}


			}
			ans.push_back(count);

		}
		return ans;
    }
};
