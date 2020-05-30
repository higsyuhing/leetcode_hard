class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int start=0, end=-1;
        while (start<words.size()){
            result.push_back(oneLine(words,maxWidth,start,end));
            start = end+1;
        }
        return result;
    }
    
    string oneLine(vector<string>& words, int maxWidth, int start, int& end){
        int l = words.size();
        int line = 0, temp;
        for (int i=start; i<l; i++){
            temp = line + words[i].length();
            if (i>start) temp++;
            if (temp>maxWidth){
                break;
            }
            end++; line=temp;
        }
        line += (start-end);
        string result="";
        if (end==l-1){
            for (int i=start; i<=end; i++){
                result += words[i];
                if (i!=end) result+=" ";
            }
            int remain = maxWidth - (line+end-start);
            string temp(remain,' ');
            return result+temp;
        }else{
            if (start==end){
                string temp(maxWidth-line,' ');
                return words[start]+temp;
            }
            int perslot = (maxWidth-line)/(end-start);
            int left = (maxWidth-line)%(end-start);
            string temp(perslot,' ');
            for (int i=start; i<=end; i++){
                result += words[i];
                if (i!=end){
                    result+=temp;
                    if (left>0){
                        result += " ";
                        left--;
                    }
                }
            }
            return result;
        }
    }
};

/*
engineering work.. 
*/
