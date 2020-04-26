class Solution {

    // 从第一题变化二来！3D整体采用BFS遍历,从四周一圈先开始; 装水量取决于周围最小的那个高度，类似木桶原理的感觉，所以BFS找最小的点based PQ而不是Queue; 弹出以后搜索四周，; 
    // 关键点I：只要差是大于0的，就把差值加入水池，说明现在我们赚了; 
    // 从第一题得来的关键点II：选用当前点和四周的较高值作为新的高度放PQ，继续探索
    
    int[][] dirs=new int[][]{{1,0},{0,1},{-1,0},{0,-1}};
    public int trapRainWater(int[][] heightMap) {
        
        int res=0;
        int m=heightMap.length;
        int n=heightMap[0].length;
        
        PriorityQueue<int[]> pq=new PriorityQueue<>((x,y)->(x[2]-y[2]));//比较高度
        boolean visited[][]=new boolean[m][n];
        
        //1.初始化四周一圈都放进来，别忘了visited
        for(int i=0;i<m;i++){
            pq.add(new int[]{i,0,heightMap[i][0]});
            pq.add(new int[]{i,n-1,heightMap[i][n-1]});
            visited[i][0]=true;
            visited[i][n-1]=true;
        }
        for(int j=0;j<n;j++){
            pq.add(new int[]{0,j,heightMap[0][j]});
            pq.add(new int[]{m-1,j,heightMap[m-1][j]});
            visited[0][j]=true;
            visited[m-1][j]=true;
        }  
        //开始BFS遍历，每次弹出最小的
        while(!pq.isEmpty()){
            int[] cur=pq.remove();
            for(int[] dir:dirs){
                int x=cur[0]+dir[0];
                int y=cur[1]+dir[1];
                if(x<0||x>=m||y<0||y>=n||visited[x][y]) continue;
                res+=Math.max(0,cur[2]-heightMap[x][y]);//关键点，只要差是大于0的，就把差值加入水池
                pq.add(new int[]{x,y,Math.max(cur[2],heightMap[x][y])});//关键点，用curMaxHeight代替当前点的高度，去木桶别人
                visited[x][y]=true;
            }
        }
        return res;    
    }
    
    
    /*
    
    // The approach here is that we start from the outermost boundary and go on shrinking it from the current weakest link (minimum height). This weakest link concept can be implemented using a minimum heap priority queue, in which we push the boundary heights and get the minimum each time.
    // We get the trapped water when we find a building with height smaller than the current weakest link, the reason is that when even the weakest link in the boundary is not allowing the water to pass through it, then the water stays. The units of water is the difference in heights of the current weakest link and the other smaller height visited just now.
    
class Solution {
public:
    struct Position {
        int x;
        int y;
        
        Position (int a = 0, int b = 0) {
            x = a;
            y = b;
        }
    };
    
	// The height and its position in one place
    class Height {
        public:
            int h;
            Position position;
        
            Height(int p = -1, int a = -1, int b = -1) {
                h = p;
                position.x = a;
                position.y = b;
            }
        
            bool operator<(const Height& h1) const {
                return h > h1.h;
            }
    };
    
    int trapRainWater(vector<vector<int>>& heightMap) {
        priority_queue<Height> minHeap;
        Height top;
        
        int m = heightMap.size();
        int n = heightMap.size() == 0 ? 0 : heightMap[0].size();
        
        vector<vector<bool>> visited(m, vector<bool> (n, 0));
        
        int water = 0;
        
		// Pushes column boundary in min heap
        for (int i = 0; i < n; i++) {
            minHeap.push(Height(heightMap[0][i], 0, i));
            visited[0][i] = 1;
            
            minHeap.push(Height(heightMap[m - 1][i], m - 1, i));
            visited[m - 1][i] = 1;
        }
        
		// Pushes row boundary in min heap
        for (int j = 1; j < m - 1; j++) {
            minHeap.push(Height(heightMap[j][0], j, 0));
            visited[j][0] = 1;
            
            minHeap.push(Height(heightMap[j][n - 1], j, n - 1));
            visited[j][n - 1] = 1;
        }
        
        while (!minHeap.empty()) {
            top = minHeap.top();
            minHeap.pop();
                     
            int x = top.position.x, y = top.position.y;            
            int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            
			// Checks the directions - top, bottom, right, left for unvisited elements
            for (int p = 0; p < 4; p++) {
                int row = x + directions[p][0];
                int col = y + directions[p][1];
                
				// If a valid unvisited element is found
                if (row >= 0 && row < m && col >= 0 && col < n && !visited[row][col]) {
                    Height next(heightMap[row][col], row, col);
                    
					// If water can be trapped (when height of this new element is less than the current weakest link) 
                    if (next.h < top.h) {
                        water += top.h - next.h;                                                
                        next.h = max(next.h, top.h);
                    }
					
					// Shrinks the boundary by pushing the new element
                    minHeap.push(next);
                    visited[row][col] = 1;
                }   
            }
        }
        
        return water;
    }
};
    
    */
    
    
    /*
    int trapRainWater(vector<vector<int>>& heightMap) {
        
        // first throught, maybe time-out
        // repeating compute the minimal holding value for row/col
        // while until no change. 
        
        if(heightMap.size() < 3) return 0; 
        if(heightMap[0].size() < 3) return 0; 
        
        
    }
    */
}
