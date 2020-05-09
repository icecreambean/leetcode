// https://leetcode.com/problems/min-cost-climbing-stairs/
// * cheaper cost (table size reduction): just store the last two states

public class DpEasy746 {
    public int minCostClimbingStairs(int[] cost) { // ith step
        if (cost.length <= 2) {
            return Math.min(cost[0], cost[1]);
        }
        int[] total = new int[cost.length];
        total[0] = cost[0];
        total[1] = cost[1];
        for (int i = 2; i < cost.length; i++) {
            total[i] = Math.min(total[i-1], total[i-2]) + cost[i];
        }
        return Math.min(total[cost.length-1], total[cost.length-2]);
    }

    public static void main(String[] args) {
        DpEasy746 p = new DpEasy746();
        int[] t = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

        //System.out.println(p.minCostClimbingStairs(new int[] {10,15,20}));
        System.out.println(p.minCostClimbingStairs(t));
    }
}