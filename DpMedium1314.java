// https://leetcode.com/problems/matrix-block-sum/
// * seems like it's just a 2D filter / convolution with zero padding
// currently O(n^4), guh

// https://leetcode.com/problems/matrix-block-sum/discuss/477036/JavaPython-3-PrefixRange-sum-w-analysis-similar-to-LC-30478
// * actual DP implementation (integral image): O(n^2) + O(1)
// DP done, where ans[y][x] = area from (0,0) to (y,x)

public class DpMedium1314 {
    public int[][] matrixBlockSum(int[][] mat, int K) {
        int[][] ans = new int[mat.length][mat[0].length];
        for (int y = 0; y < mat.length; y++) {
            for (int x = 0; x < mat[0].length; x++) { // (y,x) --> cur pos
                //System.out.printf("(%d %d)%n", y, x);
                for (int yin = Math.max(0, y-K); yin <= Math.min(y+K, mat.length-1); yin++) {
                    for (int xin = Math.max(0, x-K); xin <= Math.min(x+K, mat[0].length-1); xin++) {
                        //System.out.printf("   (%d %d)%n", yin, xin);
                        ans[y][x] += mat[yin][xin];
                    }
                }
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        // int[][] mat = {{1,2,3},{4,5,6},{7,8,9}}; int K = 1;
        int[][] mat = {{1,2,3},{4,5,6},{7,8,9}}; int K = 2;

        int[][] ans = new DpMedium1314().matrixBlockSum(mat,K);
        for (int i = 0; i < ans.length; i++) {
            for (int j = 0; j < ans[i].length; j++) {
                System.out.printf("%d ", ans[i][j]);
            }
            System.out.println("");
        }
    }
}