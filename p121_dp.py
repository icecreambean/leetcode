#!/usr/bin/env python3
#https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

#DP problem? amounts to systematic brute force O(n^2)?
# consider: 1D array for profit p[]
# for i in p[], scan through all previous entries 0 <= j < i
# find j s.t. min prices[j]
# then p[i] = prices[i] - prices[j] and find i s.t. max profit
# if all profits <= 0: return 0
#
#sorting solution:
# sort by min and max (one O(nlogn) operation)
# scan through each array to find pairwise match: O(n^2) worst case

#O(n) soln with hint :[
# hint: track both current min and max_profit
# for item i
#  compare new profit relative to old min - records max profit
#  update min if new min
#what i needed to consider is that, if it dips, then all future profits must
#be overriden by this newer lower buy price

class Solution:
    #O(n) soln: not a DP solution
    def maxProfit(self,prices):
        prfmax = 0; imin = 0
        for i,p in enumerate(prices[1:],1):
            prf = p - prices[imin]
            if prf > prfmax:
                prfmax = prf
            if p < prices[imin]:
                imin = i
        return prfmax

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
                imax = i    #imax unnecessary
        return prfmax


def main():
    mp = Solution()
    problems = [[7,1,5,3,6,4], [7,6,4,3,1], [], [5], [6,5], [5,6]]
    for p in problems:
        mpp = mp.maxProfit(p)
        print("{}    {} : {}".format(mpp == mp.maxProfitBF(p),mpp,p))

if __name__=='__main__':
    main()

#sorted_index = sorted(range(len(prices)), key=lambda i: prices[i])