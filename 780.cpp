class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        
        while(tx >= sx && ty >= sy)
        {
            if(tx == sx && ty == sy) return true;
			
            // we need aggressively substract the number.. 
            if(ty > tx)
                ty = ty-tx*std::max(1, ((ty-std::max(tx, sy))/tx));
            else
                tx = tx-ty*std::max(1, ((tx-std::max(ty, sx))/ty));
        }
        return false;
        
        
        /*
        if((sx == tx) && (sy == ty)) return true; 
        if(sx > tx) return false; 
        if(sy > ty) return false; 
        
        if(reachingPoints(sx+sy, sy, tx, ty)) return true; 
        if(reachingPoints(sx, sx+sy, tx, ty)) return true; 
        
        return false; 
        */
    }
};
