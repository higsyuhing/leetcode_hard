class Solution(object):
    def crackSafe(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        M = k**(n-1)
        P = [q*k+i for i in xrange(k) for q in xrange(M)]
        ans = []

        for i in xrange(k**n):
            j = i
            while P[j] >= 0:
                ans.append(str(j / M))
                P[j], j = -1, P[j]

        return "".join(ans) + "0" * (n-1)
