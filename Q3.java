// https://leetcode.com/problems/longest-substring-without-repeating-characters
// * so much more elegant T_T
//   https://leetcode.com/problems/longest-substring-without-repeating-characters/discuss/1729/11-line-simple-Java-solution-O(n)-with-explanation

import java.util.HashMap;

class Q3 {
    public static int lengthOfLongestSubstring(String s) {
        int curMax = 0; 
        int curTotal = 0; // easiest way to handle last curMax comparison
        HashMap<Character, Integer> hm = new HashMap<>();
        for (int i = 0; i < s.length(); i++) {
            if (hm.containsKey(s.charAt(i)) && i-hm.get(s.charAt(i)) <= curTotal) {
                //System.out.printf(" v** curTotal=%d, curMax=%d%n", curTotal, curMax);
                if (curTotal > curMax) curMax = curTotal;
                // ** note: must handle if duplicate occurred before where curTotal started
                curTotal = i - hm.get(s.charAt(i));
            } else {
                curTotal++;
            }
            hm.put(s.charAt(i),i); // overwrites prior index
            //System.out.printf(" v** {%c}: curTotal=%d%n", s.charAt(i), curTotal);
        }
        //System.out.printf(" v** max of: %d, %d%n", curMax, curTotal);
        return Math.max(curMax, curTotal);
    }

    public static void main(String args[]) {
        String[] as = {
            "ohomm", // 3
            "bdd", // 2
            "bbbbb", // 1
            "aab", // 2
            "abcabcbb", // 3
            " ", // 1
            "", // 0
            "salt", // 4
            "abcda", // 4
            "abba", // 2
            "aba", // 2
            "caba" // 3
        };
        for (String s : as) System.out.printf("%s: %s%n", s, Q3.lengthOfLongestSubstring(s));
    }
}