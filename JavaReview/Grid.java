// https://www.baeldung.com/java-multi-dimensional-arraylist - gross
// https://eclipsesource.com/blogs/2014/04/11/3-good-reasons-to-avoid-arrays-in-java-interfaces/
// * be careful with types if using low-level arrays

// .map(lambda), .forEach(lambda)
// https://winterbe.com/posts/2014/07/31/java8-stream-tutorial-examples/ (Stream = monad)

// https://stackoverflow.com/questions/13198703/java-convert-listinteger-to-string
// https://www.baeldung.com/java-8-collectors
// .stream(): entry-way into FP programming
// .collect(): fold operations (e.g. concat) on a Stream (translate to functional)
// Collectors: .toList(), .toSet(), .toCollection(LinkedList::new), .toMap(), 
//             .joining(opt str) for Stream<String> elems ... this is OP

import java.util.ArrayList;
import java.util.stream.Collectors;

public class Grid {
    public static void main(String[] args) {
        int NROWS = 4;
        int NCOLS = 5;
        // pre-define with values (use braces) for jagged array
        int[][] grid = new int[NROWS][NCOLS];
        for (int i=0; i < grid.length; i++) {
            for (int j=0; j < grid[i].length; j++) {
                System.out.printf("%d ", grid[i][j]);
            }
            System.out.println("");
        }

        ArrayList<ArrayList<Integer>> grid2 = new ArrayList<>(NROWS);
        for (int i = 0; i < NROWS; i++) { // init code
            grid2.add(new ArrayList<Integer>(NCOLS));
            for (int j = 0; j < NCOLS; j++) {
                grid2.get(i).add(0);
            }
        }
        System.out.println(grid2);
        StringBuilder sb = new StringBuilder(50); // FP string join
        for (int i = 0; i < NROWS; i++) {
            sb.append( grid2.get(i).stream().map(String::valueOf).collect(Collectors.joining(", ")) )
              .append(System.lineSeparator());
            // String.join(", ", grid2.get(i) ... <-- type issue
        }
        System.out.print(sb);
    }
}