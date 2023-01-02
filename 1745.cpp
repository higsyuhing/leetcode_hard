class Solution {
public:
    // isPalindrome for [i, j)
    bool isPalindrome(string& s, int i, int j){
        if (i >= j)
            return false; 

        while (i < j){
            if (s[i] != s[j-1])
                return false; 
            i++; 
            j--; 
        }
        return true; 
    }

    bool checkPartitioning(string s) {
        // hash table for: if substring s[i,j) is palindrome.. no.. 
        // 2 substrings are fixed: [0, i), [j, s.size())
        // so we can generate a set of palindrome i and j
        // then for each i, j pair, we check if they are valid palindrome

        vector<int> arri, arrj; 
        for (int i = 1; i <= (s.size()-2); i++){
            if (isPalindrome(s, 0, i) == true){
                arri.push_back(i); 
            }
        }
        if (arri.size() == 0)
            return false; 
        // cout << "arri: " << endl; 
        // for (int i = 0; i < arri.size(); i++){
        //     cout << arri[i] << endl; 
        // }

        for (int j = 2; j < s.size(); j++){
            if (isPalindrome(s, j, s.size()) == true){
                arrj.push_back(j); 
            }
        }
        if (arrj.size() == 0)
            return false; 
        // cout << "arrj: " << endl; 
        // for (int i = 0; i < arrj.size(); i++){
        //     cout << arrj[i] << endl; 
        // }

        int indexi, indexj; 
        indexj = 0; 
        for (indexi = 0; indexi < arri.size(); indexi++){
            int i = arri[indexi]; 
            while (i >= arrj[indexj]){ // curr start i must < curr end j
                indexj++; 
            }
            for (int currj = indexj; currj < arrj.size(); currj++){
                int j = arrj[currj]; 
                if (isPalindrome(s, i, j) == true)
                    return true; 
            }
        }

        return false; 
    }
};
