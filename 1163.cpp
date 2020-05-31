class Solution {
public:
// We use "j" to find a better starting index. If any is found, we use it to update "i"

// 1."i" is the starting index of the first substring
// 2."j" is the staring index of the second substring
// 3."k" is related to substring.length() (eg. "k" is substring.length()-1)

// Case 1 (s[i+k]==s[j+k]):
// -> If s.substr(i,k+1)==s.substr(j,k+1), we keep increasing k.
// Case 2 (s[i+k]<s[j+k]):
// -> If the second substring is larger, we update i with j. (The final answer is s.substr(i))
// Case 3 (s[i+k]>s[j+k]):
// -> If the second substring is smaller, we just change the starting index of the second string to j+k+1. Because s[j]~s[j+k] must be less than s[i], otherwise "i" will be updated by "j". So the next possible candidate is "j+k+1".

    string lastSubstring(string s) {
        int n=s.length(),i=0,j=1,k=0;
        while(j+k<n)
        {
            if(s[i+k]==s[j+k]) k++; 
            else if(s[i+k]<s[j+k]) i=j++,k=0;
            else j+=k+1,k=0;
        }
        return s.substr(i);
    }
    
    /*
    string lastSubstring(string s) {
        // assume there is a prefix to guarantee it's the last one, 
        //      thus it must be continue to the end. 
        // keep a set and a index: 
        //      set keeps the current candidate: starting pos
        //      index keeps the current depth. (some pos cannot have long string)
        
        if(s == "") return ""; 
        
        queue<int> startqueue, tempqueue; 
        int length, curr; 
        // init step
        for(int i = 0; i < s.size(); i++){
            // init case
            if(startqueue.empty()){
                startqueue.push(i); 
                curr = i; 
                continue; 
            }
            
            if(s[curr] == s[i]){ 
                // same, thus add into queue
                startqueue.push(i); 
                continue; 
            }
            else if(s[curr] < s[i]){
                // this one is later, thus clean-up queue
                while(!startqueue.empty()) startqueue.pop();
                startqueue.push(i); 
                curr = i; 
                continue; 
            }
        }
        //cout << startqueue.size() << endl; 
        
        // before go into main step: 
        // insert a partition-number
        startqueue.push(-1); 
        // be careful about end of string case.. 
        length = 1; // check: pos+i
        
        while(1){
            //cout << startqueue.size() << endl; 
            if(startqueue.size() == 2) break; // the last one and -1
            
            // by no way, we need an extra queue.. tempqueue
            while(1){
                int startpos = startqueue.front(); 
                startqueue.pop(); 
                if(startpos == -1){
                    // break and insert later
                    break; 
                }
                
                // firstly check the checking position pos+i
                // not that if we have >1 starting point, if one
                //      reaches the end of string, the other one must not. 
                // also, it will never exceed the s.size, length+1 every time
                if((startpos+length) == s.size()) continue; 
                //curr = startpos+length; 
                
                // init case
                if(tempqueue.empty()){
                    tempqueue.push(startpos); 
                    curr = startpos+length; 
                    continue; 
                }
                
                if(s[curr] == s[startpos+length]){ 
                    // same, thus add into queue
                    tempqueue.push(startpos); 
                    continue; 
                }
                else if(s[curr] < s[startpos+length]){
                    // this one is later, thus clean-up queue
                    while(!tempqueue.empty()) tempqueue.pop();
                    tempqueue.push(startpos); 
                    curr = startpos+length; 
                    continue; 
                }
            }
            // insert all tempqueue value into startqueue and -1
            swap(startqueue, tempqueue); 
            startqueue.push(-1); 
            length++; 
        }
        
        return s.substr(startqueue.front()); 
        
        
    }
    */
};
