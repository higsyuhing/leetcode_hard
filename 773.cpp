class Solution {
public:
    inline void checkpush(queue<int>& bfsqueue, set<int>& checked, int temp){
        if(checked.find(temp) == checked.end()){
            bfsqueue.push(temp); 
            checked.insert(temp); 
        }
    }
    
    int slidingPuzzle(vector<vector<int>>& board) {
        // why I feel that this is a DP problem.. 
        // total 6! = 720 different cases
        // single no matter bfs/dfs, it will explore 
        //      until all the cases has been found
        // init: 2,3,2,2,3,2 moves
        // in meanwhile: 1,2,1,1,2,1 moves.. thus in fact it will not explode.. 
        // then bfs is a good choice! 
        
        // index = a*100000 + b*10000 + c*1000 + d*100 + e*10 + f
        // target = 123450
        queue<int> bfsqueue; 
        set<int> checked; 
        int i; 
        i = board[0][0]*100000+board[0][1]*10000+board[0][2]*1000+
            board[1][0]*100+board[1][1]*10+board[1][2]; 
        if(i == 123450) return 0; 
        
        bfsqueue.push(i); 
        checked.insert(i); 
        int temp,a,b,c,d,e,f, len, step; 
        step = 0; 
        while(bfsqueue.size() > 0){
            len = bfsqueue.size(); 
            step++; 
            for(i = 0; i < len; i++){
                temp = bfsqueue.front(); 
                bfsqueue.pop(); 
                f = temp%10; temp /= 10; 
                e = temp%10; temp /= 10; 
                d = temp%10; temp /= 10; 
                c = temp%10; temp /= 10; 
                b = temp%10; temp /= 10; 
                a = temp%10; 
                if(a == 0){
                    temp = b*100000+a*10000+c*1000+d*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = d*100000+b*10000+c*1000+a*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                }
                else if(b == 0){
                    temp = b*100000+a*10000+c*1000+d*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+c*10000+b*1000+d*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+e*10000+c*1000+d*100+b*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                }
                else if(c == 0){
                    temp = a*100000+c*10000+b*1000+d*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+b*10000+f*1000+d*100+e*10+c; 
                    if(temp == 123450) return step; 
                    checkpush(bfsqueue, checked, temp); 
                }
                else if(d == 0){
                    temp = d*100000+b*10000+c*1000+a*100+e*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+b*10000+c*1000+e*100+d*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                }
                else if(e == 0){
                    temp = a*100000+b*10000+c*1000+e*100+d*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+e*10000+c*1000+d*100+b*10+f; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+b*10000+c*1000+d*100+f*10+e; 
                    if(temp == 123450) return step; 
                    checkpush(bfsqueue, checked, temp); 
                }
                else{
                    temp = a*100000+b*10000+f*1000+d*100+e*10+c; 
                    checkpush(bfsqueue, checked, temp); 
                    temp = a*100000+b*10000+c*1000+d*100+f*10+e; 
                    checkpush(bfsqueue, checked, temp); 
                }
            }
        }
        
        return -1; 
    }
};
