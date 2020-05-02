class Solution {
public:
    bool validate(vector<vector<char>>& board, int posi, int posj){
        // check if position <posi, posj> is a valid number.. 
        // board[posi][posj] should always be filled with 1-9
        
        char c = board[posi][posj]; 
        for(int i = 0; i < 9; i++){
            if(i == posi) continue; 
            if(board[i][posj] == c) return false; 
        }
        for(int j = 0; j < 9; j++){
            if(j == posj) continue; 
            if(board[posi][j] == c) return false; 
        }
        int x = posi/3; // 0, 1, 2 sub-box
        int y = posj/3; 
        for(int i = x*3; i < (x*3+3); i++){ // 0-2, 3-5, 6-8
            if(i == posi) continue; 
            for(int j = y*3; j < (y*3+3); j++){
                if(j == posj) continue; 
                if(board[i][j] == c) return false; 
            }
        }
        return true; 
    }
    
    bool solver(vector<vector<char>>& board, int pos){
        // find next position, looking for 1-9, recrusive call.. 
        
        // find next position
        while(pos < 81){
            if(board[pos/9][pos%9] != '.'){
                pos++; 
            }
            else break; 
        }
        
        // if we reach the end, return true
        if(pos == 81) return true; 
        
        // the current slot, try all possible cases
        for(int k = 0; k < 9; k++){
            board[pos/9][pos%9] = '1'+k; // try this number
            
            // if valid, then try recursively, if get true, return
            // else, try next number
            if(validate(board, pos/9, pos%9))
                if(solver(board, pos+1)) return true; 
        }
        
        // tried all numbers but all failed, make it empty and return false
        board[pos/9][pos%9] = '.'; 
        return false; 
        
        //for(int j = posj; j < 9; j++){
        //    if(board[posi][j] != '.') continue; 
        //    for(int k = 0; k < 9; k++){
        //        board[posi][j] = '1'+k; 
        //        if(validate(board, posi, j))
        //            solver(board, posi, j); 
        //    }
        //}
        //for(int i = posi+1; i < 9; i++){
        //    for(int j = 0; j < 9; j++){
        //    }
        //}
        
        // for(int curr = pos; curr < 81; curr++){
            // starting row by row, col by col
        //    int x = curr/9; 
        //    int y = curr%9; // division and get module is too costly! 
        
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        // DFS......... :(
        // for i = 0->8, j = 0->8, 
        //      if not empty, continue; else for k = 1->9, validate and recursive
        // in fact, the recursive is fine, at most 81 recursive calls.. 
        
        solver(board, 0); 
    }
};
