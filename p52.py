#!/usr/bin/env python
#https://leetcode.com/problems/n-queens-ii/description/

#suggestions
#   1. greedy (least remaining area) + rotating/flipping the board
#       doesnt work, more than one unique soln exists (e.g. see n = 5)
#(looked at theoretical answer)
#   dfs by columns
#   ...need to separate [db]fs conceptually from brute-force;
#      [db]fs only brutes along a subset of dimensions ... lots of early exits
#      i.e. not 'brute force' because you broke the problem into a smaller one?
#write in C++ to make faster...

class DfsSoln:
    def totalNQueens(self,n):
        """
        Applies DFS to construct all possible solutions to N-queens for a board 
        size n.
        """
        #edge cases (n < 4)
        if n < 0: return 0
        #dfs stack & pathtracking
        stack = [self.DfsStackItem( 0,0 )] #deliberately not using call stack
        path = []
        n_soln = 0 #counter
        #dfs loop: process the grid by column
        while len(stack) > 0:
            curpos = stack.pop()
            is_valid = self.isValidMove(curpos, path)
            #DEBUG
            #print "(%d,%d)" % (curpos.x, curpos.y), is_valid, n_soln
            #print " ", path
            
            if curpos.y < n-1 and not (is_valid and curpos.x == n-1): 
                #...not at n-queens soln (last column)
                #create move to next tile of current column
                stack.append(self.DfsStackItem(curpos.x, curpos.y+1))
            
            # (backtrack only when all possibilities in column assessed -
            #  invalid tile at end of column, or n-queens soln reached)
            should_backtrack = False

            if is_valid: #curpos
                #full soln - can backtrack (last column: only one answer)
                if curpos.x == n-1:
                    n_soln += 1
                    should_backtrack = True
                else: #curpos.x < n-1 (move to next column)
                    stack.append(self.DfsStackItem(curpos.x+1, 0))
                    path.append(curpos)
            elif curpos.y == n-1:
                #backtrack if invalid tile at end of column (no possible solns)
                should_backtrack = True
            
            if should_backtrack and len(path) > 0:
                #backtrack to most previous incomplete column
                for i in xrange(len(path)-1,-1,-1):
                    if path[i].y != n-1: break
                del path[i:]

        return n_soln


    def isValidMove(self, newpos, qlist):
        """
        Checks if a proposed position 'newpos' conflicts with the position of any
        already existing valid queen position in 'qlist'.
        """
        for q in qlist:
            #horizontal
            if q.x == newpos.x: return False
            #vertical
            if q.y == newpos.y: return False
            #diagonal: gradient == +/-1
            if abs(q.y - newpos.y) == abs(q.x - newpos.x):
                return False
            #(smarter method for diagonals: booleans for: row+col, row-col)
            #(otherwise, dfs method is completely identical)
        return True


    class DfsStackItem:
        """
        Inner class for each item in the dfs stack
        """
        def __init__(self, new_x, new_y):
            self.x = new_x
            self.y = new_y
        
        def __str__(self):
            return "(%d,%d)" % (self.x, self.y)
        def __repr__(self):
            return "(%d,%d)" % (self.x, self.y)




if __name__ == '__main__':
    d = DfsSoln()
    solns = [1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596, 
             2279184, 14772512, 95815104]
    for i in range(1,len(solns)+1):
        s = d.totalNQueens(i)
        print "n: %d, #solns: %d, %s" % (i, s, s == solns[i-1])

#old test code
def firstMoveArea(n,x,y):
    """
    Determines area covered by first piece's placement, given board size n
    and coords (x,y) referenced from bottom-left, from (0,0)
    """
    #assume (x,y) is a valid coord
    #account for NESW
    area = 2*n - 1
    #account for diagonals (4 rectangles, inclusive coords)
    rect = ( ((0,0),(x,y)), ((x,0),(n-1,y)), ((0,y),(x,n-1)), ((x,y),(n-1,n-1)) )
    for i in rect:
        botleft = i[0]; topright = i[1]; X = 0; Y = 1
        height = topright[Y] - botleft[Y] #ignore offset by 1
        width = topright[X] - botleft[X]
        if height > width: area += width
        else: area += height
    return area

def firstMoveTest():
    n = 5
    d = {}
    for x in range(n):
        for y in range(n):
            d['({},{})'.format(x,y)] = firstMoveArea(n,x,y)
    min_area = min(d.values())
    #print grid
    s = ''
    for y in range(n-1,-1,-1):
        for x in range(n):
            if d['({},{})'.format(x,y)] == min_area:
                s += '#'
            else: s += '.'
        s += '\n'
    print(s)

    #for key, val in sorted(d.items(), key=lambda (k,v): (v,k)):
    #    print("{}: {}".format(key, val))

    