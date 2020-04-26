class Solution {
public:
    // go back and check this solution once have time.. record in note.txt
    
    // The tricky point of this problem is if you dont use hash_map to help calculate distance, you cannot get very fast results. This is because in the test bench, the word length is very short, but the wordlist might be very huge. So, if you just cycle the wordlist, this will waste time.
    // I defined a new data structure: WordTree. By convert the whole wordlist into the wordtree and use dfs to fastly search this tree, we can get the total results.
    
    //构建词树结构
    struct WordTree
    {
        string content;
        vector<WordTree*> index;
        WordTree(string input) :content(input),index() {}
    };
    //判断两个字符串的相对距离是否为1
    //为1则返回ture 否则返回false
    bool check(string a, string b)
    {
        int cnt = 0;
        for (int i = 0; i < a.size(); i++)	if (a[i] != b[i]) ++cnt;
        if (cnt == 1) return true;
        return false;
    }

    //构建树结构方便查找
    //输入： 开始词，字典表，终结词在字典中的下标
    //返回： 树结构根节点指针和树的高度
    WordTree* Construct(string beginWord, vector<string>& wordList, string endWord)
    {
        WordTree* root = new WordTree(beginWord);
        unordered_set<string> words(wordList.begin(), wordList.end()); //将原数据转移到words的数组中，该数组可以直接通过下标索引
        unordered_map<string, int> dicindex; //字典查找 string 对应被使用了多少次
        //vector<int> eraseListIndex;
        queue<WordTree*> Que;
        int flag = 0;
        int cnt = 0;
        int upbound = 1;
        Que.push(root);
        WordTree* temp; //构建遍历指针
        while (!Que.empty())
        {
            ++cnt;
            auto temp = Que.front();

            for (int l = 0; l < temp->content.size(); l++)
            {
                for (char c = 'a'; c <= 'z'; c++)
                {
                    if (temp->content.at(l) == c) continue;
                    char old = temp->content.at(l); //暂存
                    temp->content.at(l) = c;
                    if (words.count(temp->content))
                    {
                        if (temp->content == endWord) flag =1;
                        temp->index.push_back(new WordTree(temp->content));
                        Que.push(temp->index.back());
                        ++dicindex[temp->content];
                    }
                    temp->content.at(l) = old;
                }
            }
            if (cnt == upbound)
            {
                if (flag == 1) break;
                unordered_set<string>::iterator test;
                for (test = words.begin();test != words.end();)
                {
                    if (dicindex[*test] > 0)
                    {
                        test = words.erase(test); //如果这个字符不是终止字符，那么就删除
                    }
                    else test++;
                }
                dicindex.clear();
                upbound = Que.size() - 1;
                cnt = 0;
            }
            Que.pop();
        }
        return root;
    }

    //从树结构中查找目标endWord，
    //输入 根节点，endWord，当前步长i
    //返回二维数组 res
    void helper(WordTree *root, int step, string endWord, vector<vector<string>> &res,vector<string> &tempres)
    {
        tempres.push_back(root->content);
        if (root->index.size() == 0)
        {
            if (root->content != endWord) return;
            else
            {
                res.push_back(tempres);
                return;
            }
        }
        else if (root->index.size() != 0)
        {
            for (auto &i : root->index)
            {
                helper(i, step + 1, endWord, res, tempres);
                tempres.pop_back();
            }
        }
        return;
    }


    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<string>::iterator temp;
        vector<vector<string>> res;
        vector<string> tempres;
        temp = find(wordList.begin(), wordList.end(), endWord);
        if (temp == wordList.end()) return res;

        //wordList.erase(temp);
        if (check(beginWord, endWord))
        {
            tempres.push_back(beginWord);
            tempres.push_back(endWord);
            res.push_back(tempres);
            return res;
        }
        temp = find(wordList.begin(), wordList.end(), beginWord);
        if (temp != wordList.end()) wordList.erase(temp);
        WordTree *root = Construct(beginWord, wordList, endWord);
        helper(root, 0, endWord, res, tempres);
        return res;
    }
    
};


/*
    // this is another solution for fast execution time.. 
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size();
        vector<vector<string>> res;
        unordered_map<string, vector<string>> children;
        unordered_set<string> words(wordList.begin(), wordList.end());
        
        if(words.find(endWord) == words.end())
            return res;
        
        if(beginWord == endWord)
        {
            res.push_back({beginWord});
            return res;
        }
        
        unordered_set<string> fromStart, fromEnd;
        fromStart.insert(beginWord);
        fromEnd.insert(endWord);
        bfs(fromStart, children, words, fromEnd, false);
        vector<string> l;
        l.push_back(beginWord);
        getPath(beginWord,l, res, endWord, children);
        return res;
    }
    
    void getPath(string& beginWord, vector<string>& l, vector<vector<string>>& res, string endWord, unordered_map<string, vector<string>>& children)
    {
        if(endWord == beginWord)
        {
            res.push_back(l);
            return;
        }
        
        for(int i = 0; i < children[beginWord].size(); i++)
        {
            l.push_back(children[beginWord][i]);
            getPath(children[beginWord][i], l, res, endWord, children);
            l.pop_back();
        }
    }
    
    void bfs(unordered_set<string>& fromStart, unordered_map<string, vector<string>>& children, unordered_set<string>& words, unordered_set<string>& fromEnd, bool reverse)
    {
        // prevent infinite loop.
        if(fromStart.size() == 0)
            return;
        
        if(fromStart.size() > fromEnd.size())
        {
            bfs(fromEnd, children, words, fromStart, !reverse);
            return;
        }
        
        unordered_set<string> nxt; // the next frontier.
        bool done = false; // need this to get all paths.
        unordered_set<string> remove; // need this if node has multiple parents.       
        
        
        for(auto it = fromStart.begin(); it != fromStart.end(); it++)
            words.erase(*it);
        
        for(auto it = fromStart.begin(); it != fromStart.end(); it++)
        {
            string s = *it;
            for(int i = 0; i < s.length(); i++)
            {
                char old = s[i];
                string ow = s;
                for(int c = 'a'; c <= 'z'; c++)
                {
                    s[i] = c;
                    if(words.find(s) != words.end())
                    {
                        if(fromEnd.find(s) != fromEnd.end())
                        {
                            done = true;
                        }
                        else
                        {
                            nxt.insert(s);
                        }
                        
                        if(reverse)
                            children[s].push_back(ow);
                        else
                            children[ow].push_back(s);
                    }
                }
                s[i] = old;
            }
        }
        
        if(!done)
            bfs(nxt, children, words, fromEnd, reverse);
    }

*/


/*
    // this python solution is out of time limit. 
    
    def findLadders(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """
        # this is based on the solution of lc127
        
        # this is really good.. see some hardness of leetcode! 

        if endWord not in wordList or not endWord or not beginWord or not wordList:
            return []

        # Since all words are of same length.
        L = len(beginWord)

        # Dictionary to hold combination of words that can be formed,
        # from any given word. By changing one letter at a time.
        all_combo_dict = defaultdict(list)
        for word in wordList:
            for i in range(L):
                # Key is the generic word
                # Value is a list of words which have the same intermediate generic word.
                all_combo_dict[word[:i] + "*" + word[i+1:]].append(word)


        # Queue for BFS
        queue = collections.deque([([beginWord], beginWord)])
        queue.append(([], ""))
        # Visited to make sure we don't repeat processing same word.
        visited = {beginWord: True}
        finallist = []
        while queue:
            wordlist, current_word = queue.popleft()      
            if current_word == "": 
                if finallist: 
                    return finallist
                queue.append(([], ""))
                continue
            
            for i in range(L):
                # Intermediate words for current word
                intermediate_word = current_word[:i] + "*" + current_word[i+1:]

                # Next states are all the words which share the same intermediate state.
                for word in all_combo_dict[intermediate_word]:
                    # If at any point if we find what we are looking for
                    # i.e. the end word - we can return with the answer.
                    if word == endWord:
                        templist = list(wordlist)
                        templist.append(word)
                        finallist.append(templist)
                        continue
                    # Otherwise, add it to the BFS Queue. Also mark it visited
                    if word not in visited:
                        visited[word] = True
                        templist = list(wordlist)
                        templist.append(word)
                        queue.append((templist, word))
                # all_combo_dict[intermediate_word] = []
        return []
    

*/
