Trie = lambda: collections.defaultdict(Trie)
WEIGHT = False

class WordFilter(object):
    def __init__(self, words):
        self.trie = Trie()

        for weight, word in enumerate(words):
            word += '#'
            for i in xrange(len(word)):
                cur = self.trie
                cur[WEIGHT] = weight
                for j in xrange(i, 2 * len(word) - 1):
                    cur = cur[word[j % len(word)]]
                    cur[WEIGHT] = weight

    def f(self, prefix, suffix):
        cur = self.trie
        for letter in suffix + '#' + prefix:
            if letter not in cur:
                return -1
            cur = cur[letter]
        return cur[WEIGHT]


'''
Consider the word 'apple'. For each suffix of the word, we could insert that suffix, followed by '#', followed by the word, all into the trie.

For example, we will insert '#apple', 'e#apple', 'le#apple', 'ple#apple', 'pple#apple', 'apple#apple' into the trie. Then for a query like prefix = "ap", suffix = "le", we can find it by querying our trie for le#ap.
'''


# Your WordFilter object will be instantiated and called as such:
# obj = WordFilter(words)
# param_1 = obj.f(prefix,suffix)

'''

class WordFilter {
public:
    
    // a prefix tire and a suffix tire? 
    
    #define ALPHABET_SIZE   26
    // trie node 
    typedef struct TrieNode { 
        struct TrieNode *children[ALPHABET_SIZE]; 

        // weight, init with -1
        int val; 
    } TrieNode_t; 
    TrieNode_t *root_pre, *root_suf; 
    
    TrieNode_t *newNode(){
        TrieNode_t *res = new TrieNode_t(); 
        res->val = -1; 
        for(int i = 0; i < ALPHABET_SIZE; i++)
            res->children[i] = NULL; 
        return res; 
    }
    
    void inner_insert(string word, int weight) {
        // insert into root_pre
        TrieNode_t *curr = root_pre; 
        for(int i = 0; i < word.size(); i++){
            if(curr->children[(int)(word[i]-'a')] == NULL){
                curr->children[(int)(word[i]-'a')] = newNode(); 
                curr = curr->children[(int)(word[i]-'a')]; 
            }
            else curr = curr->children[(int)(word[i]-'a')]; 
        }
        curr->val = weight; 
        
        // insert into root_suf
        curr = root_suf; 
        for(int i = word.size()-1; i >= 0; i--){
            if(curr->children[(int)(word[i]-'a')] == NULL){
                curr->children[(int)(word[i]-'a')] = newNode(); 
                curr = curr->children[(int)(word[i]-'a')]; 
            }
            else curr = curr->children[(int)(word[i]-'a')]; 
        }
        curr->val = weight; 
    }
    
    WordFilter(vector<string>& words) {
        for(int i = 0; i < words.size(); i++) inner_insert(words[i], i); 
    }
    
    int f(string prefix, string suffix) {
        // a fact is that, for intersect, we only need to find the maximum weight
        // construct sorted vector for pre-set and suf-set, 
        // then use 2 pointers to find out.. 
        
        
        
        
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */

'''
