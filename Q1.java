// https://leetcode.com/problems/two-sum/submissions/ (EASY)
// O(n) implementation with a HashMap: saddddd

import java.util.Arrays;
import java.lang.Comparable;
import java.util.Comparator;

import java.util.HashMap;

class Q1 {
    
    public int[] twoSum(int[] nums, int target) { // O(n)
        // key: desired val to pair with;   val: index
        HashMap<Integer, Integer> hm = new HashMap<>();
        for (int i=0; i<nums.length; i++) { // autoboxing
            int k = target-nums[i];
            if (hm.containsKey(k)) {
                return new int[] {Math.min(hm.get(k),i), Math.max(hm.get(k),i)};
            }
            hm.put(nums[i], i);
        }
        return new int[] {-1,-1};
    }

    // public int[] twoSum(int[] nums, int target) { // O(n*log(n))
    //     //int[] sorted = Arrays.copyOfRange(nums, 0, nums.length);
    //     Pair[] sorted = new Pair[nums.length];
    //     for (int i = 0; i < nums.length; i++) {
    //         sorted[i] = new Pair(nums[i],i); // array contents initially unassigned (null ptr)
    //     }
    //     Arrays.sort(sorted);
    //
    //     for (int left = 0; left < nums.length; left++) {
    //         if (target-sorted[left].val < sorted[left].val) break;
    //         int right = Arrays.binarySearch(sorted, left+1, sorted.length, 
    //                                         new Pair(target-sorted[left].val, 0));
    //                                         // comparable won't care about the index val
    //         if (right < 0) continue;
    //         if (sorted[left].val + sorted[right].val == target) 
    //             return new int[] {sorted[left].index, sorted[right].index};
    //     }
    //     return new int[] {-1,-1};
    // }
    //
    // private class Pair implements Comparable<Pair>, Comparator<Pair> {
    //     int val;
    //     int index;
    //     public Pair(int val, int index) { this.val = val; this.index = index; }
    //
    //     public int compareTo(Pair p) { return this.val - p.val; }
    //     public int compare (Pair p1, Pair p2) { return p1.val - p2.val; }
    // };

    public static void main(String args[]) {
        // int[] nums = {2,7,11,15};
        // int target = 9;

        int[] nums = {3,6,3};
        int target = 6;

        int[] ans = new Q1().twoSum(nums, target);
        System.out.printf("[%d,%d]\n", ans[0], ans[1]);
    }
}