// https://leetcode.com/problems/divisor-game/ (EASY)
// lmaooo this is a one-line game theory problem

// https://leetcode.com/problems/divisor-game/discuss/274566/just-return-N-2-0-(proof)
// * 1 (lose), 2 (win), 3 (lose), 4 (win)
// * if you lose overall at N-1, then you will win at N, 
//   because you can simply decrement by 1
// * (odd numbers will always give back an even number to the opponent)
// https://leetcode.com/problems/divisor-game/discuss/274592/how-are-we-supposed-to-know-the-optimal-strategy-of-the-game
// * combinatorial game theory </3

public class DpEasy1025 {

    public boolean divisorGame(int N) {
        boolean[] state = new boolean[N+1];
        state[0] = false; // no moves
        state[1] = false; // no moves
        if (N <= 1) return false;
        for (int n = 2; n < N+1; n++) {
            boolean canWin = false;
            for (int x = 1; x < n; x++) {
                if (n % x != 0) continue; // needs improv
                if (!(state[n-x])) {
                    canWin = true;
                    break;
                }
            }
            state[n] = canWin;
        }
        return state[N];
    }

    public static void main(String[] args) {
        Dp1025 p = new Dp1025();
        System.out.println(p.divisorGame(2));
    }
}