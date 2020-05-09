// https://leetcode.com/problems/count-square-submatrices-with-all-ones/
// Q: what does the DP cache represent? the actual soln? or some other property?
//  * must draw out and visualise the DP cache

// https://leetcode.com/problems/count-square-submatrices-with-all-ones/discuss/441620/DP-with-figure-explanation
// * DP cache: min size of possible squares: (up, left, corner) + 1, if 1
// * ans: sum of DP cache (cell = #squares with common vertex)

public class DpMedium1277 {
    public int countSquares(int[][] matrix) {
        int[][] cache = new int[matrix.length][matrix[0].length];
        int total = 0;
        for (int y = 0; y < matrix.length; y++) {
            for (int x = 0; x < matrix[0].length; x++) {
                if (x < 1 || y < 1) {
                    cache[y][x] = matrix[y][x];
                } else if (matrix[y][x] == 1) {
                    cache[y][x] = Math.min(Math.min(cache[y-1][x-1], cache[y][x-1]), cache[y-1][x]) + 1;
                }
                total += cache[y][x];

                // (too naive...)
                // int up = (y-1 >= 0) ? ans[y-1][x] : 0;
                // int left = (x-1 >= 0) ? ans[y][x-1] : 0;
                // int corner = (x-1 >= 0 && y-1 >= 0) ? ans[y-1][x-1] : 0;
                // ans[y][x] = up + left - corner + matrix[y][x];
            }
        }
        print2D(cache);
        return total;
        //return cache[matrix.length-1][matrix[0].length-1];
    }

    public void print2D(int[][] ans) {
        for (int i = 0; i < ans.length; i++) {
            for (int j = 0; j < ans[i].length; j++) {
                System.out.printf("%d ", ans[i][j]);
            }
            System.out.println("");
        }
    }

    // \[([0-9]+,)\]
    // {$1}
    // test: [0,1,1,1]

    public static void main(String[] args) {
        // int[][] matrix = {
        //     {1,0,1},
        //     {1,1,0},
        //     {1,1,0}
        // };

        int[][] matrix = {
            {0,1,1,1},
            {1,1,1,1},
            {0,1,1,1}
        };

        System.out.println(new DpMedium1277().countSquares(matrix));
    }
}