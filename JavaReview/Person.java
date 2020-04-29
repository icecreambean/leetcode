// https://www.java67.com/2015/05/4-ways-to-concatenate-strings-in-java.html
// platform independent newline: https://www.baeldung.com/java-string-newline
// primitive types: https://softwareengineering.stackexchange.com/questions/203970/when-to-use-primitive-vs-class-in-java
//  * only consider under generics: https://docs.oracle.com/javase/tutorial/java/data/autoboxing.html
// `final`: https://stackoverflow.com/questions/4971286/javas-final-vs-cs-const/4971323
// right bitshift: https://stackoverflow.com/questions/29333425/difference-between-sign-propagating-right-shift-and-zero-fill-right-shift-in-jav
// array vs ArrayList: https://www.quora.com/What-is-the-difference-between-an-array-and-an-array-list
// cloning: https://www.geeksforgeeks.org/clone-method-in-java-2/
//  * assignment operator: by reference (of object) => shallow copy of object
// ...
// var-args: `...` just converts remaining args into an array[] (single type)

// (endIndex is always exclusive)
// scanf/regex: https://docs.oracle.com/javase/7/docs/api/java/util/Scanner.html
//  * java.util.regex.Matcher/Pattern: similar to Perl
// java.util.Collections: binarySearch, sort: https://docs.oracle.com/javase/7/docs/api/java/util/Collections.html
// java.util.Date; java.util.SimpleDateFormat: .format(), .parse()
// java.util.GregorianCalendar: .setTime(Date)

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;

import java.util.Collections;
import java.util.Comparator; // generic interface: has compare(a,b)
// java.util.Comparable: has compareTo() - for default sorting; set by Override class defn
// https://www.journaldev.com/780/comparable-and-comparator-in-java-example
//  * in sort(), only Comparator<>() can be the second arg

public class Person implements Cloneable {
    private String name;
    private int age;

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public int getAge() { return age; }
    public String getName() { return name; }
    
    @Override
    public String toString() { 
        // no real benefit to StringBuilder here under javac optimisation
        //return name + "(" + Integer.toString(age) + ")"; 
        // StringBuilder sb = new StringBuilder(40);
        // sb.append(name).append('(').append(age).append(')');
        // return sb.toString();
        return String.format("%s(%d)", name, age);
    }

    // needs to implement Cloneable interface
    @Override
    public Object clone() throws CloneNotSupportedException {
        Person p = (Person)super.clone();
        p.name = this.name;
        p.age = this.age;
        return (Object)p;
    }

    @Override
    public boolean equals(Object o) {
        // this; same class; same state
        if (o == this) return true;
        if (!(o instanceof Person)) return false;
        Person p = (Person)o; // typecast ref
        if (this.name.compareTo(p.name) == 0 && this.age == p.age) return true;
        return false;
    }

    //######################################
    public static final String FOOBAR = "Foobar";

    public static void pad(List<Integer> l) {l.add(0);} // objects --> pass by ref

    public static void main(String[] args) throws CloneNotSupportedException 
    {
        for (int i = 0; i < args.length; i++) System.out.println(args[i]);

        //Person[] people = {new Person("Victor", 24), new Person("Charlie", 50)};
        LinkedList<Person> people = new LinkedList<Person>(); // doubly-linked
        people.add(new Person("Victor", 24));
        people.add(new Person("Charlie", 50));
        //for (int i = 0; i < people.size(); i++) { Person p = people.get(i);
        for (Person p: people) {
            System.out.printf("%s has %d IQ.%n", p.getName(), p.getAge());
            System.out.println(p.toString());
        }
        Person p1 = new Person("Thomas", 1);
        Person p2 = (Person) p1.clone();
        System.out.printf("%s %s%n", p1,p2);
        System.out.println(p1.equals(p2));
        System.out.println(p1.equals(people.get(0)));

        // pass-by-value, pass-by-ref
        ArrayList<Integer> li1 = new ArrayList<Integer>();
        li1.add(3); pad(li1);
        System.out.println(li1);
        
        String s = "Hello";
        // sorting the list
        // https://www.baeldung.com/java-8-sort-lambda
        people.add(p1);
        // Collections.sort(people, new Comparator<Person>() { // inner "interface"
        //     public int compare(Person p1, Person p2) { // single method
        //         //System.out.printf("\"%s\" can be seen%n", s); // YES
        //         return (p1.getAge() - p2.getAge()); //p1.compareTo(p2);
        //     }
        // });
        // ** looks like Haskell, lambdas/inner functions preserve outside scope...
        //Collections.sort(people, (Person pp1, Person pp2) -> pp1.getAge() - pp2.getAge());
        Collections.sort(people, (Person pp1, Person pp2) -> {
            return pp1.getAge() - pp2.getAge(); // multi-line lambda (when braced)
        });
        //Person pp1 = new Person("Korone", 29); // no comparator name collision if defined after
        
        System.out.println(people);

    }
}