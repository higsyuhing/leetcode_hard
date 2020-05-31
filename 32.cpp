class Solution {
public:
    int longestValidParentheses(string s) {
        // similar to question: 1249, but
        // compute the maximum distance between all of them, including start/end
        // This one is not hard.. 
        
        stack<pair<char, int>> sstack; 
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '('){
                sstack.push(make_pair('(', i));
            }
            else{
                if(sstack.empty())
                    sstack.push(make_pair(')', i));
                else if(sstack.top().first == '(')
                    sstack.pop(); 
                else
                    sstack.push(make_pair(')', i));
            }
        }
        
        int curr = s.size(); 
        int length = 0; 
        
        // note that the order in stack is in-ordered. 
        while(!sstack.empty()){
            if(length < (curr - (sstack.top().second+1)))
                length = curr - (sstack.top().second+1); 
            curr = sstack.top().second; 
            sstack.pop(); 
        }
        if(length < curr) length = curr; 
        
        return length; 
    }
};
