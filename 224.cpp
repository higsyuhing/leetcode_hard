class Solution {
public:
    int calculate(string s) {
        stack <int> nums, ops;
        int64_t num = 0;
        int rst = 0;
        int sign = 1;
        for (char c : s) { 
            if (isdigit(c)) {
                num = num * 10 + c - '0';
            }
            else {
                rst += sign * num;
                num = 0;
                if (c == '+') sign = 1;
                if (c == '-') sign = -1;
                if (c == '(') {
                    nums.push(rst);
                    ops.push(sign);
                    rst = 0;
                    sign = 1;
                }
                if (c == ')' && ops.size()) {
                    rst = ops.top() * rst + nums.top();
                    ops.pop(); nums.pop();
                }
            }
        }
        rst += sign * num;
        return rst;
    }
};

/*
Jamie mentioned 2 things: 
- evaluate when ')'
- keep sign with the number

#define VALSEP  (1LL << 32)
class Solution {
public:
    int calculate(string s) {
        stack<int64_t> calval; 
        stack<char> calop; 
        bool flageval = false; 
        for (int index = 0; index < s.size(); index++){
            // parse next token.. 
            if (s[index] == ' ')
                continue; 
            char token = ' '; 
            int64_t num = 0; 
            if (s[index] >= '0' && s[index] <= '9'){
                for (; index < s.size(); index++){
                    if (s[index] >= '0' && s[index] <= '9'){
                        num = num*10 + ((int64_t)(s[index] - '0')); 
                    }
                    else{
                        index--; // index++ in outer loop. 
                        break; 
                    }
                }
            }
            else{
                token = s[index]; 
            }

            cout << "token: " << token << ", num: " << num << endl; 

            // calculate
            if (token == ' '){ // we are number
                if (flageval == false){
                    calval.push(num); 
                }
                else{
                    // evaluate
                    int64_t val2 = num; 
                    token = calop.top(); 
                    int64_t val1 = 0; 
                    if (!calval.empty() && calval.top() != VALSEP){ // e.g. (-1) --> (0-1)
                        val1 = calval.top(); 
                        calval.pop(); 
                    }
                    int64_t val = 0; 
                    if (token == '+'){
                        val = val1 + val2; 
                    }
                    else if (token == '-'){
                        val = val1 - val2; 
                    }
                    else{
                        cout << "Error 1: token invalid: " << token << endl; 
                        return 0; 
                    }
                    calval.push(val); 
                    flageval = false; 
                }
            }
            else{ // we are token
                if (token == '+' || token == '-'){
                    calop.push(token); 
                    flageval = true; 
                    continue; 
                }
                if (token == '('){
                    calval.push(VALSEP); 
                    token = (flageval == true) ? 't' : 'f'; 
                    calop.push(token); 
                    calop.push('p'); 
                    flageval = false; 
                }
                else{ // ')'
                    if (calop.top() != 'p'){
                        cout << "Error 2: calop.top not 'p': " << calop.top() << endl; 
                        return 0; 
                    }
                    int64_t val2 = 0; 
                    if (calval.top() != VALSEP){ // e.g. () --> 0
                        val2 = calval.top(); 
                        calval.pop(); 
                    }
                    if (calval.top() != VALSEP){
                        cout << "Error 3: calval.top not VALSEP: " << calval.top() << endl; 
                        return 0; 
                    }
                    calval.pop(); // VALSEP
                    calop.pop(); // 'p'
                    token = calop.top(); calop.pop(); // 't/f'
                    flageval = (token == 't') ? true : false; 
                    if (flageval == false){
                        calval.push(val2); 
                    }
                    else{
                        token = calop.top(); 
                        int64_t val1 = 0; 
                        if (!calval.empty() && calval.top() != VALSEP){ // e.g. (-1) --> (0-1)
                            val1 = calval.top(); 
                            calval.pop(); 
                        }
                        int64_t val = 0; 
                        if (token == '+'){
                            val = val1 + val2; 
                        }
                        else if (token == '-'){
                            val = val1 - val2; 
                        }
                        else{
                            cout << "Error 4: token invalid: " << token << endl; 
                            return 0; 
                        }
                        calval.push(val); 
                        flageval = false; 
                    }
                }
            }
        }
        if (calval.empty())
            return 0; 
        else
            return ((int)(calval.top())); 
    }
};
*/
