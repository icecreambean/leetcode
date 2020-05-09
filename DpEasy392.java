// https://leetcode.com/problems/is-subsequence/

// https://leetcode.com/problems/is-subsequence/discuss/87258/2-lines-Python
// * cool FP
// https://leetcode.com/problems/is-subsequence/discuss/87268/Java-code-for-the-follow-up-question
// * follow-up soln :o
// * HashMap for key: a-z, val: indexes
// * ??: does binarySearch to reduce search time scanning on t
// * (does this misunderstand the follow-up question?)

// https://leetcode.com/problems/is-subsequence/discuss/87297/Java.-Only-2ms.-Much-faster-than-normal-2-pointers.
// * very interesting. same time complexity soln, but
// * actually cheaper due to fewer Java function calls

class DpEasy392 {
    public boolean isSubsequence(String s, String t) {
        if (s.length() == 0) return true;
        if (t.length() == 0) return false;
        int si = 0;
        for (int ti = 0; ti < t.length(); ti++) {
            if (t.charAt(ti) == s.charAt(si)) {
                si++;
                if (si == s.length()) return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        // String s = "abcdef";
        // System.out.println(s.charAt(0));
        String s = "axc";
        String t = "ahbgdc";
        System.out.println(new DpEasy392().isSubsequence(s, t));
    }
}