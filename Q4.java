// https://leetcode.com/problems/median-of-two-sorted-arrays/

// IDEA:
// Do a Binary Search that will iteratively improve the indexes until it can be
// determined where the median indexes are

import java.util.Arrays;

public class Q4 {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        int totalLength = nums1.length + nums2.length;// convenience-only
        int medianIndex = (nums1.length + nums2.length)/2; // target; convenience-only
        // * odd  (m+n): floor((m+n)/2)
        // * even (m+n): floor((m+n)/2)=x, x-1
        // [modified binary search: search on nums1, including comparison from nums2]
        int lower1Bound = 0; int upper1Bound = nums1.length-1;
        //int lower2Bound = 0; int upper2Bound = nums2.length-1;
        int cur1Index = nums1.length/2; int cur2Index = 0;
        int cur2IndexPos = 0; // convenience-only
        int nAbove = 0; // convenience-only

        while (nAbove != medianIndex) { //&& lower1Bound <= upper1Bound && lower2Bound <= upper2Bound) {
            //cur2Index = Arrays.binarySearch(nums2, lower2Bound, upper2Bound, nums1[cur1Index]);
            cur2Index = Arrays.binarySearch(nums2, nums1[cur1Index]);
            //if (cur2Index < 0) cur2Index = nums2.length + cur2Index; 
            // ** special case if -ve, and result is front/end list
            // ** indicates median value likely not in one of the two lists
            cur2IndexPos = (cur2Index < 0) ? nums2.length-1 + cur2Index : cur2Index;
            nAbove = cur1Index + cur2IndexPos;
            System.out.printf(" v** nAbove=%d%n", nAbove);

            // handle special negative cases
            if (cur2Index == -1) {//-lower2Bound -1) {
                // ** nums1[upper] < num2 [lower]
                //System.out.printf(" v** %d,%d %d,%d%n", lower1Bound, upper1Bound, lower2Bound, upper2Bound);
                //System.out.printf(" v** %d,%d%n", lower1Bound, upper1Bound);
                

            } else if (cur2Index == -nums2.length -1) {//-upper2Bound -1) {
                // ** nums2 [upper] < num1[lower]
                System.out.printf(" v** %d,%d%n", lower1Bound, upper1Bound);

            }

            if (nAbove == medianIndex) { // at median value
                break; // median found
            } else if (nAbove < medianIndex) { // move to upper region; both values should be similar
                lower1Bound = cur1Index;
                //lower2Bound = cur2IndexPos;
            } else {
                upper1Bound = cur1Index;
                //upper2Bound = cur2IndexPos;
            }

            System.out.printf("nums1: %s(%d={%d}), %d,%d%n", arrayToString(nums1), cur1Index, nums1[cur1Index], lower1Bound, upper1Bound);
            System.out.printf("nums2: %s(%d,%d={%d})%n", arrayToString(nums2), cur2Index, cur2IndexPos, nums2[cur2IndexPos]);
            cur1Index = lower1Bound + (upper1Bound - lower1Bound +1)/2;
            System.out.printf(" ^** new cur1 index: %d%n", cur1Index);
        }
        
        System.out.println("[END]:");
        System.out.printf("nums1: %s(%d), %d,%d%n", arrayToString(nums1), cur1Index, lower1Bound, upper1Bound);
        System.out.printf("nums2: %s(%d,%d)%n", arrayToString(nums2), cur2Index, cur2IndexPos);
        // compute median for even case
        if (totalLength % 2 == 0) return (nums1[cur1Index] + nums2[cur2Index])/2;
        // compute median for odd case: only 1 valid index, expect the other to be out of bounds
        if (cur1Index < 0 || cur1Index >= nums1.length) return nums2[cur2Index];
        return nums1[cur1Index];
    }

    public static String arrayToString(int[] a) {
        StringBuilder sb = new StringBuilder();
        for (int e: a) {
            sb.append(e);
            sb.append(" ");
        }
        return sb.toString();
    }

    public static void main(String args[]) {
        int[][] a = new int[][] {
            {1,2,10,13,15}, {3,14,17,43}, // 13
            {1,2,3}, {50,51,52,53}, // 50
            {1,2,3}, {50,51,52}, // avg(3,50)
            {1,2,3,4}, {50,51}, // avg(3,4)
            {1,50,51}, {2,3,4} // avg(3,4)
        };

        System.out.println(Arrays.binarySearch(a[0], 16));

        Q4 q = new Q4();
        for (int i = 0; i < a.length; i += 2) {
            // actual answer
            int[] tempA = new int[a[i].length + a[i+1].length];
            int j = 0;
            for (int e: a[i]) tempA[j++] = e;
            for (int e: a[i+1]) tempA[j++] = e;
            Arrays.sort(tempA);
            int mid = tempA.length/2;
            double expected = (tempA.length % 2 == 0) ? (tempA[mid] + tempA[mid-1])/2 : tempA[mid];
            double actual = q.findMedianSortedArrays(a[i],a[i+1]);
            System.out.printf("%d)  [%s], [%s]: expect=%.3f, got=%.3f ----> %b%n%n%n", 
                              i/2, Q4.arrayToString(a[i]), Q4.arrayToString(a[i+1]), 
                              expected, actual, expected == actual);
        }
    }
}