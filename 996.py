class Solution(object):
    def numSquarefulPerms(self, A):
        N = len(A)
        count = collections.Counter(A)

        graph = {x: [] for x in count}
        for x in count:
            for y in count:
                if int((x+y)**.5 + 0.5) ** 2 == x+y:
                    graph[x].append(y)

        def dfs(x, todo):
            count[x] -= 1
            if todo == 0:
                ans = 1
            else:
                ans = 0
                for y in graph[x]:
                    if count[y]:
                        ans += dfs(y, todo - 1)
            count[x] += 1
            return ans

        return sum(dfs(x, len(A) - 1) for x in count)
    
    '''
        // add up two biggest numbers in A, and test their square root
        // then explain a table for reference
        // then for each element, find the pair the could match
        // for number has K neighbors, it could have C(K, 2) cases
        // if it only has 2 neighbors, the position is kind of fixed
        // if only has 1 neighbor, guaranteed at the beginning/end
        // use a DFS to explore all cases.. 
        
        
    '''
