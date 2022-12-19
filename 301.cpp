class Solution {
public:

    void construct_right(string& s, vector<string>& ret, unordered_set<string>& hash, 
        vector<int>& rightpos, vector<int>& leftsel, 
        vector<int>& leftpos, vector<int>& righteli, vector<int>& rightsel, int rpos){

        if (rpos == righteli.size()){
            // perform elimination, check duplicate and record
            // eliminate
            string tmp(s); 
            for (int i = 0; i < rightsel.size(); i++){
                int pos = leftpos[rightsel[i]]; // from big to small
                tmp.erase(pos, 1); 
            }
            for (int i = leftsel.size()-1; i >= 0; i--){
                int pos = rightpos[leftsel[i]]; // from big to small, due to i. 
                tmp.erase(pos, 1); 
            }

            // check duplication and record
            if (hash.count(tmp) == 0){
                ret.push_back(tmp); 
                hash.insert(tmp); 
            }
            return; 
        }

        int eliindex = righteli[rpos]; 
        int lastindex = leftpos.size()-1; 
        if (rightsel.size() > 0){
            lastindex = rightsel.back()-1; 
        }
        for (int i = lastindex; i >= 0; i--){
            int currpos = leftpos[i]; 
            if (currpos >= eliindex){
                rightsel.push_back(i); // from big to small
                construct_right(s, ret, hash, 
                    rightpos, leftsel, leftpos, righteli, rightsel, rpos+1); 
                rightsel.pop_back(); 
            }
            else{
                break; 
            }
        }
    }


    void construct_left(string& s, vector<string>& ret, unordered_set<string>& hash, 
        vector<int>& rightpos, vector<int>& lefteli, vector<int>& leftsel, int lpos, 
        vector<int>& leftpos, vector<int>& righteli, vector<int>& rightsel){

        if (lpos < 0){
            construct_right(s, ret, hash, 
                rightpos, leftsel, leftpos, righteli, rightsel, 0); 
            return; 
        }

        int eliindex = lefteli[lpos]; 
        int lastindex = 0; 
        if (leftsel.size() > 0){
            lastindex = leftsel.back()+1; 
        }
        for (int i = lastindex; i < rightpos.size(); i++){
            int currpos = rightpos[i]; 
            if (currpos <= eliindex){
                leftsel.push_back(i); // from small to big
                construct_left(s, ret, hash, 
                    rightpos, lefteli, leftsel, lpos-1, 
                    leftpos, righteli, rightsel); 
                leftsel.pop_back(); 
            }
            else{
                break; 
            }
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        // use stack to check extra parentheses: pair of char and index
        // based on each one, set up corresponding sets of elimintation
        // generate results

        stack<pair<char, int>> stack_extp; 
        vector<int> leftpos, rightpos; // position of parentheses
        for (int i = 0; i < s.size(); i++){
            char curr = s[i]; 
            if (curr != '(' && curr != ')')
                continue; // ignore letters

            if (curr == '('){
                leftpos.push_back(i); 
                stack_extp.push(make_pair(curr, i)); 
            }
            else{
                rightpos.push_back(i); // ')'
                if (!stack_extp.empty()){
                    auto& p = stack_extp.top(); 
                    if (p.first == '('){
                        stack_extp.pop(); // cancel out '('
                    }
                    else{
                        stack_extp.push(make_pair(curr, i)); // push ')'
                    }
                }
                else{ // empty, push
                    stack_extp.push(make_pair(curr, i)); // push ')'
                }
            }
        }

        // debug
        // while (!stack_extp.empty()){
        //     auto& p = stack_extp.top(); 
        //     cout << p.first << ", " << p.second << endl; 
        //     stack_extp.pop(); 
        // }

        vector<string> ret; 
        if (stack_extp.empty()){ // original string is valid.. return
            ret.push_back(s); 
            return ret; 
        }

        // only 2 sets of cases: [)..)][(..(]
        vector<int> lefteli, righteli; 
        while (!stack_extp.empty()){
            auto& p = stack_extp.top(); 
            if (p.first == '('){
                righteli.push_back(p.second); // left parentheses
            }
            else{
                lefteli.push_back(p.second); // right parentheses
            }
            // cout << p.first << ", " << p.second << endl; 
            stack_extp.pop(); 
        }
        // right eli should always on the right side of left eli. 
        if (righteli.size() > 0 && lefteli.size() > 0){
            int rightlastpos = righteli[righteli.size()-1]; 
            int leftlastpos = lefteli[0]; 
            if (rightlastpos < leftlastpos){
                cout << "error? right < left.. " << 
                rightlastpos << " : " << leftlastpos << endl; 
            }
        }
        
        // create sets of elimintation
        // use curr location and left/right pos
        unordered_set<string> hash; 
        vector<int> leftsel, rightsel; // select targets
        construct_left(s, ret, hash, 
            rightpos, lefteli, leftsel, lefteli.size()-1, 
            leftpos, righteli, rightsel); 

        return ret; 
    }
};
