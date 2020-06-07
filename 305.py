class Solution(object):
    def numIslands2(self, m, n, positions):
        """
        :type m: int
        :type n: int
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        class DSU(object):
            def __init__(self, length):
                self.par = list(range(length))
                self.isLand = [False] * length
                self.rank = [1] * length
                self.count = 0

            def find(self, x):
                if self.par[x] != x:
                    self.par[x] = self.find(self.par[x])
                return self.par[x]

            def union(self, x, y):
                px, py = self.find(x), self.find(y)
                if px == py:
                    return False
                if self.rank[px] > self.rank[py]:
                    self.par[py] = px
                elif self.rank[px] < self.rank[py]:
                    self.par[px] = py
                else:
                    self.par[py] = px
                    self.rank[py] += 1
                self.count -= 1
                return True

            def addLand(self, x):
                self.isLand[x] = True
                self.count += 1

        def index(x, y):
            return x * n + y

        dsu = DSU(m * n)
        res = list()
        for p in positions:
            x, y = p[0], p[1]
            dsu.addLand(index(x, y))
            if x > 0 and dsu.isLand[index(x - 1, y)]:
                dsu.union(index(x, y), index(x - 1, y))
            if x < m - 1 and dsu.isLand[index(x + 1, y)]:
                dsu.union(index(x, y), index(x + 1, y))
            if y > 0 and dsu.isLand[index(x, y - 1)]:
                dsu.union(index(x, y), index(x, y - 1))
            if y < n - 1 and dsu.isLand[index(x, y + 1)]:
                dsu.union(index(x, y), index(x, y + 1))
            res.append(dsu.count)
        return res
    '''
    from: 
    https://baihuqian.github.io/2018-08-02-number-of-islands-ii/
    classic DSU question.. 
    '''
