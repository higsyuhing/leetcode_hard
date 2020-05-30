class Solution {
public:
    
    vector<string> numToString = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
    
    vector <string> tenthString = {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    
    vector <string> teens = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    
    vector <string> levelTxt = {"", "Thousand", "Million", "Billion", "Trillion"};
        
    string numberToWords(int num) {
        int cnt = 0;
        string result = "";
        
        if (num <= 10)
            return numToString[num];
        
        while (num != 0) {
            string  text = "";
            int val = num % 1000;
            
            getTextForVal(val, text);
           
            if (val > 0 && cnt > 0)
                text += levelTxt[cnt] + " ";
           
            result = text + result;
            
            num = num / 1000;
            cnt++;
        }
        
        return result.substr(0, result.length() - 1);
    }
    
    void getTextForVal(int val, string& text) {
        int num[3] = {0,0,0};
        int idx = 2;
        
        while (val != 0) {
            num[idx] = val % 10;
            val = val / 10;
            idx--;
        }
        
        if (num[0] != 0) {
            text = text + numToString[num[0]] + " Hundred "; 
        }
        
        if (num[1] > 1) {
            text = text + tenthString[num[1] - 1] + " ";
        }
        
        if (num[1] == 1) {
            text += teens[num[2]] + " ";
        }
        
        if (num[1] != 1 && num[2] != 0) {
            text = text + numToString[num[2]] + " ";
        }
    }
};

/*
this one is not funny... 
*/
