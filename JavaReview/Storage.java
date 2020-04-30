import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.TreeSet;

public class Storage {
    public static void main(String[] args) {
        // key-val: Name-Score
        // .get(K), .put(K,V), .getOrDefault(K,V), .replace(K,V,V)
        //Map<String, Integer> hm = new TreeMap<>(); // default: sort by K
        Map<String, Integer> hm = new HashMap<>();
        hm.put("Alpha", 95);
        hm.put("Beta", 70);
        hm.put("Charlie", 84);
        System.out.println(new TreeSet<String>(hm.keySet()));

        //System.out.println(hm);
        //for (String k: hm.keySet()) System.out.printf("%s: %d%n", k, hm.get(k));
        //hm.forEach((k,v) -> System.out.printf("%s: %d%n", k,v));
        hm.replaceAll((k,v) -> { // must return V return type
            return v+5;
        });

        hm.forEach((k,v) -> { // must be void return type
            System.out.printf("%s: %d%n", k,v);
        });
    }
}