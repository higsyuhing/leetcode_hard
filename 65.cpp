class Solution {
public:
    bool isNumber(string s) {
        // this is a compiler matching.. given regular expression: 
        //      ...?? 
        
        s = removeEmpty(s);
        return isNumE(s);
    }
    
    bool isNumE(string s){
        int l = s.length();
        if (l==0) return false;
        int pos = s.find("e");
        if (pos<0) return isNum(s);
        return isNum(s.substr(0,pos)) && isInt(s.substr(pos+1));
    }
    
    bool isInt(string s){
        s = removeEmpty(s);
        int l = s.length();
        if (l==0) return false;
        for (int i=0; i<l; i++){
            if (s[i]<'0'||s[i]>'9') return false;
        }
        return true;
    }
    
    bool isNum(string s){
        int dot = 0;
        int l = s.length();
        bool hasNum = false;
        for (int i=0; i<l; i++){
            if (s[i]=='.') {
                dot++;
                if (dot>1) return false;
            }
            else if (s[i]<'0'||s[i]>'9') return false;
            else hasNum = true;
        }
        return hasNum;
    }
    
    string removeEmpty(string s){
        int l = s.length();
        int start = 0;
        int end = l-1;
        for (int i=0; i<s.length(); i++){
            if (s[i]!=' ') break;
            start++;
        }
        for (int i=l-1; i>=start; i--){
            if (s[i]!=' ') break;
            end--;
        }
        if (s[start]=='+'||s[start]=='-') start++;
        return s.substr(start,end-start+1);
    }
    
};
