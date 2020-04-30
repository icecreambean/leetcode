//package JavaReview;
// excellent revision: https://www.tutorialspoint.com/java/java_quick_guide.htm
// https://www.quora.com/Why-do-many-software-engineers-not-like-Java

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Scanner;

import java.io.IOException;
// import java.io.FileNotFoundException;
// import java.io.FileReader;
// import java.io.FileWriter;

public class IOTest {

    public static void main(String[] args) {
        // any path separator works
        StringBuilder fn = new StringBuilder(40);
        fn.append("..").append(File.separator);
        fn.append("JavaReview").append(File.separator).append("input.txt");
        File fp  = new File(fn.toString()); // can do dir operations on File obj
        File fpw = new File("output.txt");

        // https://stackoverflow.com/questions/11655020/why-does-a-try-catch-block-create-new-variable-scope
        // * try-catch has internal scope, as does if/while/etc.
        try(FileInputStream fisr = new FileInputStream(fp); // for binary-data
            FileOutputStream fisw = new FileOutputStream(fpw))
        {
            // "try-with-resources": automatic resource management
            // * class must implement AutoCloseable interface
            // * brackets can be multi-line, for multiple resources
            //FileReader reader = new FileReader(fp);
            //reader.close();
            Scanner sc = new Scanner(fisr);

            // read all lines
            while(sc.hasNextLine()) {
                String s = sc.nextLine().trim(); // trim() leading/trailing whitespace
                // String manipulation is regex by default
                String[] words = s.split("\\s+");
                if (words.length < 3) continue;
                //for (String w: words) System.out.println(w);
                String name = words[0];
                int year = Integer.parseInt(words[1]);
                StringBuilder trait = new StringBuilder(words[2]);
                trait.setCharAt(0, Character.toUpperCase(trait.charAt(0)));

                // write modified lines to output
                String output = String.format("%s %s lived around %d.%n", trait, name, year);
                System.out.printf(output);
                fisw.write(output.getBytes()); // this writer is only for bytes...
            }

        //} catch (FileNotFoundException e) {
        } catch (IOException e) { // required in "try-with-resources"
            // exception handling
            System.out.println(e.getClass().getCanonicalName()); // error type
            System.out.println(e.getMessage());
            e.printStackTrace(); // printStackTrace
            return;
        } // finally { }

        // https://www.javatpoint.com/how-to-read-file-line-by-line-in-java

    }
}


// try(FileReader reader = new FileReader(fp);
//     FileWriter writer = new FileWriter(fpw)) { } ...

// hashCode:
// converting the internal address of the object into an integer
// for hashCode() to cooperate with equals(), equivalent objects => same hash

// data structures:
// List: ArrayList, LinkedList

// https://stackoverflow.com/questions/3590677/how-to-do-union-intersect-difference-and-reverse-data-in-java
// Set:  HashSet (unordered), LinkedHashSet (records insert ordering), TreeSet (SortedSet)
// * union: new set; .addAll() x2
// * intersect: new set; .retainAll()
// * difference: new set; .removeAll()  -- inherited from base classes

// HashMap, TreeMap, (WeakHashMap, LinkedHashMap, IdentityHashMap)
// * TreeSet/Map: provide comparator on initialisation (default: ascending order)
// https://stackoverflow.com/questions/5999736/java-hashmap-with-or-without-type
// * HashMap<String, Integer> map = new HashMap<>();  -- introduced in Java 5,7
// * HashMap hm = new HashMap(); -- not recommended; equivalent to <?,?>; requires casting

// Tree: sorted ordering
// LinkedHash: insertion ordering
// Hash: unordered

// https://stackoverflow.com/questions/3524862/when-should-i-use-a-treemap-over-a-priorityqueue-and-vice-versa
// PriorityQueue: priority heap; provide Comparator at construction time
// * implementation not synchronised
// * PriorityQueue interface only gives you minimum/maximum element, unlike TreeMap
// * TreeMap has more overhead, but it allows you to access any element

// https://www.java67.com/2014/10/how-to-create-and-initialize-two-dimensional-array-java-example.html
// int[][]: https://stackoverflow.com/questions/2154251/any-shortcut-to-initialize-all-array-elements-to-zero#comment24769314_7181518
// * default value (0) on initialisation
// * java.util.Arrays: .fill(), .sort(), .asList() --> List<T>

// https://www.cs.cmu.edu/~adamchik/15-121/lectures/Binary%20Heaps/heaps.html - needs review