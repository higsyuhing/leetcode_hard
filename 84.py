class TreeNode(object): 
    def __init__(self, val, index, left, right):
        self.val = val
        self.index = index
        self.left = left
        self.right = right
        pass
        
        
    
class Tree(object):
    def __init__(self):
        self.rootNode = None
        pass
    
    def insert(self, val, index):
        node = TreeNode(val, index, None, None)
        if self.rootNode == None: 
            self.rootNode = node
            return
        else: 
            temp = self.rootNode
            parent = temp
            while temp.val < node.val: 
                if temp.index > node.index: 
                    parent = temp
                    temp = temp.left
                    pass
                else: 
                    parent = temp
                    temp = temp.right
                    pass
                if temp == None: 
                    break
                    pass
                pass
            # 2 cases: temp.val > node.val; temp == None
            if temp == None: 
                if parent.index > node.index: 
                    parent.left = node
                    return
                else: 
                    parent.right = node
                    return
                pass
            else: 
                #............. re-construct????
    

class Solution(object):
    def getMax(self, sortTree, i, j): 
        # sortTree: tree of (value, heights index), left, right
        # get Max from [i, j)
        if i >= j: 
            return 0
        Minheight = sortheights[0][0]
        Max0 = (j-i)*Minheight
        k = sortheights[0][1]
        subsort1 = []
        subsort2 = []
        for index in range(len(sortheights)-1): 
            curr = index + 1
            if sortheights[curr][1] < k: 
                subsort1.append(sortheights[curr])
                pass
            else: 
                subsort2.append(sortheights[curr])
                pass
            pass
        Max1 = self.getMax(subsort1, i, k)
        Max2 = self.getMax(subsort2, k+1, j)
        return max(Max0, Max1, Max2)
    
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        sortheights = []
        for index in range(len(heights)): 
            sortheights.append([heights[index], index, 0, 0])
            pass
        sortheights.sort()
        return self.getMax(sortheights, 0, len(heights))

    

'''
class Solution(object):
    def getMax(self, sortheights, i, j): 
        # sortheights: list of (value, heights index)
        # get Max from [i, j)
        if i >= j: 
            return 0
        Minheight = sortheights[0][0]
        Max0 = (j-i)*Minheight
        k = sortheights[0][1]
        subsort1 = []
        subsort2 = []
        for index in range(len(sortheights)-1): 
            curr = index + 1
            if sortheights[curr][1] < k: 
                subsort1.append(sortheights[curr])
                pass
            else: 
                subsort2.append(sortheights[curr])
                pass
            pass
        Max1 = self.getMax(subsort1, i, k)
        Max2 = self.getMax(subsort2, k+1, j)
        return max(Max0, Max1, Max2)
    
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        sortheights = []
        for index in range(len(heights)): 
            sortheights.append([heights[index], index])
            pass
        sortheights.sort()
        return self.getMax(sortheights, 0, len(heights))
'''

'''     
class Solution(object):
    def Base(self, heights, i, j):
        # base for range [i, j)
        Min = -1
        for index in range(i,j): 
            if Min == -1: 
                Min = heights[index]
                pass
            if Min > heights[index]: 
                Min = heights[index]
                pass
            pass
        return (j-i)*Min
    
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        # AreaTable, no, I don't need any table, just brute force all cases
        Max = 0
        for i in range(len(heights)): 
            for j in range(i, len(heights)): 
                temp = self.Base(heights, i, j+1)
                if Max < temp: 
                    Max = temp
                    pass
                pass
            pass
        return Max
'''
        
        
