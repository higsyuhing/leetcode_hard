class Solution(object):
    def criticalConnections(self, n, connections):
        """
        :type n: int
        :type connections: List[List[int]]
        :rtype: List[List[int]]
        """
        
        # graph construction
        graph = [[] for i in range(n)]
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)
        
        # depth initialization
        depths = [-1] * n
        results = []
        
        """
        visit every node exactly once, the starting point does not matter
        (as long as graph is connected)
        """
        def dfs(prev_node, cur_node, cur_depth):
            depths[cur_node] = cur_depth
            min_depth = cur_depth
            for neighbor in graph[cur_node]:
                if neighbor == prev_node: continue
                """
                find the temporary depth reached by a neighbor
                """
                temp_depth = depths[neighbor]
                if temp_depth == -1:
                    temp_depth = dfs(cur_node, neighbor, cur_depth+1)
                """
                if the returned depth is deeper, then it is a critical connection
                else, update the min_depth
                """
                if temp_depth > cur_depth:
                    results.append([cur_node, neighbor])
                else:
                    min_depth = min(min_depth, temp_depth)
            """
            return the minimum depth reached by a node
            """
            depths[cur_node] = min_depth
            return min_depth
        
        # start at node-0
        dfs(None, 0, 0)
        
        return results
        
        
'''
You might see many solutions suggest to track something called "rank" which is usually defined as the order of a DFS/BFS search. It's confusing. I spent some time understanding this question, and hope my understanding can save you some time.

In this question, we only need to keep track of the minimum depth of a node. Because for a node "u", if the returned depth (minimum) of it's neighbor "v" is strictly larger than the depth itself, then (u, v) is a critical edge.

The only caveat is that the definifition of "depth" is slightly tricky, which will not be overided by a direct connection but can be overided by backtracking (because of cycles).

For example, if the depth of "u" is 0 and "v" is an unexplored neighbor of "u", then we should first update "v" with depth=1, by walking from u to v (direct connection). However, if "u" and "v" are in a big cycle, the depth of "u", which is 0 will be propageted to "v" by other edges, so in the end, "v" will also have depth=0, and (u,v) is not a critical connection. Here, you can also see that if such cycles do not exist, then "u" would have depth 0 and "v" would have depth 1, so (u,v) is a critical connection.

I hope the code is simple enough to explain itself. Please feel free to leave any comment if this still confuses you.
'''

        
'''
        // a naive solution is, for each connection
        //   try to check the graph connection, if failed, then add into return set
        //      speed-up will be, start from one end, 
        //      if reach the other end, ret with true
        // do we have better solution?? 
        
        // OK of course, we have teh better solution for checking cycles.. 
        
'''
