// https://leetcode.com/problems/add-two-numbers/
// * cleaner :o
//   https://leetcode.com/problems/add-two-numbers/discuss/1158/Java-solution-concise-and-easy-to-understand

class Q2 {
    public class ListNode {
        int val;
        ListNode next;
        ListNode() {}
        ListNode(int val) { this.val = val; }
        ListNode(int val, ListNode next) { this.val = val; this.next = next; }
        
        public String toString() { 
            String s = Integer.toString(val) + "->";
            if (next == null) return s + "n";
            else return s + next.toString();
        }

        public int length() { 
            if (next == null) return 1;
            return 1 + next.length(); 
        }
    }

    public ListNode makeList(int[] vals, int idx) { // assume 1+ elem
        if (idx >= vals.length) return null;
        ListNode cur = new ListNode();
        cur.val = vals[idx];
        if (idx < vals.length-1) {
            cur.next = makeList(vals, idx+1);
        }
        return cur;
    }

    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        if (l1 == null) return l2;
        if (l2 == null) return l1;
        ListNode n1 = l1; ListNode n2 = l2; int carry = 0;
        ListNode curResult = new ListNode(); // having to do this init condition sucks
        ListNode headResult = curResult;
        for (; n1 != null && n2 != null; n1 = n1.next, n2 = n2.next) {
            //System.out.printf("n1 %b, n2 %b%n", n1 == null, n2 == null);
            curResult.val = n1.val + n2.val + carry;
            //System.out.println(curResult.val);
            carry = curResult.val / 10;
            curResult.val %= 10;

            if (n1.next != null && n2.next != null) {
                curResult.next = new ListNode();
                curResult = curResult.next;
            }
        }
        // handle remaining n1 or n2, and carry over value
        ListNode p = n1;
        if (n1 == null) p = n2;
        for (; p != null; p = p.next) {
            curResult.next = new ListNode(p.val + carry);
            curResult = curResult.next;
            
            carry = curResult.val / 10;
            curResult.val %= 10;
        }

        if (carry == 1) curResult.next = new ListNode(1);
        return headResult;   
    }

    public static void main(String args[]) {
        // int[] l1 = new int[] {2,4,3};
        // int[] l2 = new int[] {5,6,4};

        int[] l1 = new int[] {9,9};
        int[] l2 = new int[] {1,1,1,1};
        Q2 q = new Q2();

        ListNode ln1 = q.makeList(l1, 0);
        ListNode ln2 = q.makeList(l2, 0);

        System.out.println(q.addTwoNumbers(ln1,ln2));
    }
}