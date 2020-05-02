/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * interface Robot {
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     public boolean move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     public void turnLeft();
 *     public void turnRight();
 *
 *     // Clean the current cell.
 *     public void clean();
 * }
 */

// also see: http://www.noteanddata.com/leetcode-489-Robot-Room-Cleaner-java-solution-note.html
class Solution {
    private int[][] dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    public void cleanRoom(Robot robot) {
        Set<String> visited = new HashSet<>();
        dfs(robot, visited, 0, 0, 0);
    }
    
    private void dfs(Robot robot, Set<String> visited, int row, int col, int curDir) {
        String key =  row + ":" + col;
        if (visited.contains(key)) return;
        
        visited.add(key);
        robot.clean();
        for (int i = 0; i < 4; i++) {
            if (robot.move()) {
                
                dfs(robot, visited, row + dirs[curDir][0], col + dirs[curDir][1], curDir);
                robot.turnLeft();
                robot.turnLeft();
                robot.move();
                robot.turnLeft();
                robot.turnLeft();
            } 
            
            robot.turnRight();
            curDir = (curDir + 1) % 4;  
        }
        
    }
}
