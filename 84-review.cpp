class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        
        // use height and pos, and sweep from left to right.. 
        // compute only when the value needs to evict-out.. 
        
        int tmpmax = 0; 
        stack<int> stackheight, stackpos; 
        
        // guaranteed heights.length >= 1. 
        stackheight.push(heights[0]); 
        stackpos.push(0); 
        
        for (int i = 1; i < heights.size(); i++){
            int curr = heights[i]; 
            int currpos = i; 
            
            while ((!stackheight.empty()) && (curr < stackheight.top())){
                int last = stackheight.top(); 
                int pos = stackpos.top(); 
                
                int area = last*(i - pos); 
                currpos = pos; 
                //cout << "last, pos, i, area: " << last << ", " << pos << ", " << i << ", " << area << endl; 
                tmpmax = (area > tmpmax) ? area : tmpmax; 
                
                stackheight.pop(); 
                stackpos.pop(); 
            }
            
            stackheight.push(curr); 
            stackpos.push(currpos); 
        }
        
        // insert a "0" at the end. 
        int len = heights.size(); 
        while (!stackheight.empty()){
            int last = stackheight.top(); 
            int pos = stackpos.top(); 
            int area = last*(len - pos); 
            //cout << "last, pos, i, area: " << last << ", " << pos << ", " << len << ", " << area << endl; 
            tmpmax = (area > tmpmax) ? area : tmpmax; 
            stackheight.pop(); 
            stackpos.pop(); 
        }
        
        return tmpmax; 
    }
};

// wow.. these years, I really make progress..... 
