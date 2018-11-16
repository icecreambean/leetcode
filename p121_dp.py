#!/usr/bin/env python3
#https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

#DP problem? amounts to systematic brute force O(n^2)?
# consider: 1D array for profit p[]
# for i in p[], scan through all previous entries 0 <= j < i
# find j s.t. min prices[j]
# then p[i] = prices[i] - prices[j] and find i s.t. max profit
# if all profits <= 0: return 0
#
#can't you just search for max and min in list? O(n)? 
# max diff => order of acquisition is important
# i: scan up to find min; j: scan down to find max
# TODO what stop condition?
#

class Solution:
    #O(n) soln: not a DP solution
    def maxProf(self,prices):

        return 0

    #brute force DP: O(n^2), not fast enough
    def maxProfitBF(self,prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        #if len(prices) < 2: return 0
        #max profit, and the sell day it occurs
        prfmax = 0; imax = 0
        for i,pi in enumerate(prices[1:],1):
            pj = min(prices[:i])
            prf = pi - pj
            if prf > prfmax:
                prfmax = prf
                imax = i
        return prfmax


def main():
    mp = Solution()
    problems = [[7,1,5,3,6,4], [7,6,4,3,1], [], [5], [6,5], [5,6]]
    for p in problems:
        print("{} : {}".format(mp.maxProfit(p),p))

if __name__=='__main__':
    main()
