class Solution {
public:

    // take jamie's idea: from two sides and push to the middle
    // if we see the remaining, return hash
    // if we meet the same, recursion: left++, right--; 
    // if diff: 
    //      recursion: 1. left++, 2. right--, and compare both side's result, then +1
    // keep the result into a hash
    int helper(string& s, int left, int right, unordered_map<int, int>& hash){
        int key = (left+1)*1000+right; 
        if ( (left == right) || ((left-1) == right) ){
            hash[key] = 0; 
            return 0; 
        }

        if (hash.count(key) != 0){
            return hash[key]; 
        }

        if (s[left] == s[right]){
            return helper(s, left+1, right-1, hash); 
        }

        int resl = helper(s, left+1, right, hash); 
        int resr = helper(s, left, right-1, hash); 
        int res = (resl < resr) ? resl : resr; 
        res++; 
        hash[key] = res; 

        // cout << left << ", " << right << ", " << res << endl; 
        return res; 
    }

    int minInsertions(string s) {
        unordered_map<int, int> hash; 
        return helper(s, 0, s.size()-1, hash); 
    }
};


/*
update with jamie's answer
        // dp problem: given 2 strings, how many chars to add to make them identical
        // shift mid point, left, right substrings.. 
        // [0, left), [right, s.size()), left == right or left+1 == right
        // left = [0, s.size]
*/
