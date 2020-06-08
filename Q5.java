// https://leetcode.com/problems/longest-palindromic-substring/
// * didn't think this was DP at all...
//   https://leetcode.com/problems/longest-palindromic-substring/discuss/2921/Share-my-Java-solution-using-dynamic-programming

import java.util.LinkedList;
import java.util.Queue;

public class Q5 {
    public String longestPalindrome(String s) { // O(n^2): DP
        return s;
    }

    // public String longestPalindrome(String s) { // O(n^3): tries every example
    //     if (s.length() < 2) return s;
    //     class Item {
    //         int startPos;
    //         public int curPos;
    //         public Item(int startPos, int curPos) { 
    //             this.startPos = startPos;
    //             this.curPos = curPos;
    //         }
    //     };
    //     Queue<Item> queue = new LinkedList<Item>();  // BFS
    //     String result = "";
    //     for (int i = 0; i < s.length()-1; i++) {
    //         queue.add(new Item(i, i)); // n-1 starting positions
    //     }
    //     while (!queue.isEmpty()) {
    //         Item curItem = queue.remove();
    //         String curString = s.substring(curItem.startPos, curItem.curPos+1);
    //         boolean foundPalindrome = isPalindrome(curString); 
    //         if (foundPalindrome && curString.length() > result.length()) {
    //             result = curString;
    //         }
    //         curItem.curPos += 1;
    //         if (curItem.curPos >= s.length()) continue;
    //         queue.add(curItem);
    //     }
    //     return result;
    // }

    // boolean isPalindrome(String s) {
    //     for (int i = 0, j = s.length()-1; i < j; i++, j--) {
    //         if (s.charAt(i) != s.charAt(j)) return false;
    //     }
    //     return true;
    // }

    public static void main(String[] args) {
        Q5 q = new Q5();
        String[] tests = {
            "babad", 
            "cbbd",
            "vaomxdtiuwqlwhgutkhxxhccsgvyoaccuicgybnqnslogtqhblegfudagpxfvjdacsxgevvepuwthdtybgflsxjdmmfumyqgpxatvdypjmlapccaxwkuxkilqqgpihyepkilhlfkdrbsefinitdcaghqmhylnixidrygdnzmgubeybczjceiybowglkywrpkfcwpsjbkcpnvfbxnpuqzhotzspgebptnhwevbkcueyzecdrjpbpxemagnwmtwikmkpqluwmvyswvxghajknjxfazshsvjkstkezdlbnkwxawlwkqnxghjzyigkvqpapvsntojnxlmtywdrommoltpbvxwqyijpkirvndwpgufgjelqvwffpuycqfwenhzrbzbdtupyutgccdjyvhptnuhxdwbmdcbpfvxvtfryszhaakwshrjseonfvjrrdefyxefqfvadlwmedpvnozobftnnsutegrtxhwitrwdpfienhdbvvykoynrsbpmzjtotjxbvemgoxreiveakmmbbvbmfbbnyfxwrueswdlxvuelbkrdxlutyukppkzjnmfmclqpkwzyylwlzsvriwomchzzqwqglpflaepoxcnnewzstvegyaowwhgvcwjhbbstvzhhvghigoazbjiikglbqlxlccrwqvyqxpbtpoqjliziwmdkzfsrqtqdkeniulsavsfqsjwnvpprvczcujihoqeanobhlsvbzmgflhykndfydbxatskf"
        };
        for (String t: tests) {
            System.out.printf("'%s'[%d] ----> %s%n", t, t.length(), q.longestPalindrome(t));
        }
    }
}