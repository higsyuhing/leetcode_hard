class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int histo[10]; 
        int sumdigits = 0; 
        for (int i = 0; i < 10; i++)
            histo[i] = 0; 
        for (int i : digits){
            histo[i]++; 
            sumdigits += i; 
        }

        if (sumdigits % 3 == 0){
            goto finalize; 
        }
        int num1e, num2e; // eliminate num
        if (sumdigits % 3 == 1){
            if (histo[1] > 0 || histo[4] > 0 || histo[7] > 0){
                num1e = 1; 
                num2e = 0; 
            }
            else{
                num2e = 2; 
                num1e = 0; 
            }
        }
        if (sumdigits % 3 == 2){
            if (histo[2] > 0 || histo[5] > 0 || histo[8] > 0){
                num1e = 0; 
                num2e = 1; 
            }
            else{
                num2e = 0; 
                num1e = 2; 
            }
        }

        // eliminate
        while (num1e > 0){
            if (histo[1] > 0){
                histo[1]--; 
            }
            else if (histo[4] > 0){
                histo[4]--; 
            }
            else if (histo[7] > 0){
                histo[7]--; 
            }
            else{
                cout << "error 1" << endl; 
            }
            num1e--; 
        }
        while (num2e > 0){
            if (histo[2] > 0){
                histo[2]--; 
            }
            else if (histo[5] > 0){
                histo[5]--; 
            }
            else if (histo[8] > 0){
                histo[8]--; 
            }
            else{
                cout << "error 2" << endl; 
            }
            num2e--; 
        }

finalize: 
        // merge
        string ret = ""; 
        for (int i = 9; i >= 0; i--){
            string tmp(histo[i], 48+i); 
            ret += tmp; 
        }
        if (ret[0] == '0'){
            ret = "0"; 
        }
        return ret; 
    }
};

/*
class Solution {
public:
    inline int m_abs(int x){
        return (x > 0) ? x : -x; 
    }

    string largestMultipleOfThree(vector<int>& digits) {
        // take all digits, then form a string.. 
        int histo[10]; 
        for (int i = 0; i < 10; i++)
            histo[i] = 0; 
        for (int i : digits){
            histo[i]++; 
        }

        int numr1, numr2; 
        numr1 = histo[1] + histo[4] + histo[7]; 
        numr2 = histo[2] + histo[5] + histo[8]; 
        // we firstly group them by 3, then pair them. 
        if (m_abs(numr1 - numr2) < 3){
            numr1r = numr1; 
            numr2r = numr2; 
        }
        else{
            if ()
        }

        int numr1p = numr1 / 3; 
        int numr2p = numr2 / 3; 
        int numr1r = numr1 % 3; 
        int numr2r = numr2 % 3; 


        int num1e, num2e; // eliminate num
        if (numr1r == 0 || numr2r == 0){
            num1e = numr1r; 
            num2e = numr2r; 
        }
        else if (numr1r == numr2r){
            num1e = 0; 
            num2e = 0; 
        }
        else{
            if (numr1r > numr2r){
                num1e = numr1r - numr2r; 
                num2e = 0; 
            }
            else{
                num1e = 0; 
                num2e = numr2r - numr1r; 
            }
        }

        // eliminate
        while (num1e > 0){
            if (histo[1] > 0){
                histo[1]--; 
            }
            else if (histo[4] > 0){
                histo[4]--; 
            }
            else if (histo[7] > 0){
                histo[7]--; 
            }
            else{
                cout << "error 1" << endl; 
            }
            num1e--; 
        }
        while (num2e > 0){
            if (histo[2] > 0){
                histo[2]--; 
            }
            else if (histo[5] > 0){
                histo[5]--; 
            }
            else if (histo[8] > 0){
                histo[8]--; 
            }
            else{
                cout << "error 2" << endl; 
            }
            num2e--; 
        }

        // merge
        string ret = ""; 
        for (int i = 9; i >= 0; i--){
            string tmp(histo[i], 48+i); 
            ret += tmp; 
        }
        if (ret[0] == '0'){
            ret = "0"; 
        }
        return ret; 
    }
};
*/
