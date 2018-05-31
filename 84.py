class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        # use the solution: monotonous stack
        heights = [0] + heights + [0]
        stack = []
        slen = 0
        Max = 0
        index = 0
        while index < len(heights): 
            if (slen == 0) or (heights[stack[slen - 1]] <= heights[index]): 
                stack = stack + [index]
                slen = slen + 1
                index = index + 1
                pass
            else: 
                height = heights[stack[slen - 1]]
                del stack[slen - 1]
                slen = slen - 1
                curr = stack[slen - 1] + 1
                Max = max(Max, (index - curr)*height)
                pass
            pass
        return Max


'''
class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        # use the solution: monotonous stack
        heights = [-1] + heights + [-1]
        stack = []
        slen = 0
        Max = 0
        index = 0
        #print heights
        continueflag = 1
        while index < len(heights): 
            if (slen == 0) or (heights[stack[slen - 1]] < heights[index]): 
                stack = stack + [index]
                slen = slen + 1
                index = index + 1
                continueflag = 1
                pass
            elif heights[stack[slen - 1]] == heights[index]:
                if (index == stack[slen - 1] + continueflag): 
                    index = index + 1
                    continueflag = continueflag + 1
                    pass
                else: 
                    stack = stack + [index]
                    slen = slen + 1
                    index = index + 1
                    continueflag = 1
                    pass
            else: 
                height = heights[stack[slen - 1]]
                del stack[slen - 1]
                slen = slen - 1
                curr = stack[slen - 1] + 1
                Max = max(Max, (index - curr + 1 - continueflag)*height)
                continueflag = 1
                pass
            #print Max, stack
            pass
        return Max
'''
    
    
'''
class Solution(object):
    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """
        # use the solution: monotonous stack
        heights = [0] + heights + [0]
        stack = []
        slen = 0
        Max = 0
        for index in range(len(heights)): 
            while 1: 
                if (slen == 0) or (heights[stack[slen - 1]] <= heights[index]): 
                    stack = stack + [index]
                    slen = slen + 1
                    break
                    pass
                height = heights[stack[slen - 1]]
                del stack[slen - 1]
                slen = slen - 1
                curr = stack[slen - 1] + 1
                Max = max(Max, (index - curr)*height)
                pass
            #print Max, stack
            pass
        return Max
        
'''

'''
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
            return True
        else: 
            temp = self.rootNode
            parent = temp
            while temp.val <= node.val: 
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
                    return True
                else: 
                    parent.right = node
                    return True
                pass
            else: 
                print "Incorrect case! should not occur temp.val > node.val:" + str(node.index) + ':' + str(node.val)
                return False
                pass
            pass
        pass
    
    def printTree(self, node, depth): 
        if node == None: 
            return
        self.printTree(node.left, depth+1)
        print depth*' ' + str(node.index) + ':' + str(node.val)
        self.printTree(node.right, depth+1)
        return

class Solution(object):
    def getMax(self, sortTreeNode, i, j): 
        # sortTreeNode: tree node of (value, index), left, right
        # get Max from [i, j)
        if (i >= j) or (sortTreeNode == None): 
            return 0
        Minheight = sortTreeNode.val
        Max0 = (j-i)*Minheight
        Max1 = self.getMax(sortTreeNode.left, i, sortTreeNode.index)
        Max2 = self.getMax(sortTreeNode.right, sortTreeNode.index+1, j)
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
        # print sortheights
        indextree = Tree()
        for curr in sortheights: 
            indextree.insert(curr[0], curr[1])
            pass
        # indextree.printTree(indextree.rootNode, 0)
        return self.getMax(indextree.rootNode, 0, len(heights))
'''

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
        
        
