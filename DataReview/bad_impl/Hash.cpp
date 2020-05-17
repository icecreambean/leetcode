#include <iostream>
#include <vector>
#include <string>

//#include <sstream>
// #include <unordered_map> // C++11 hash table: hashing provided separately, in std::hash<>()?
// * https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key

// size_type: https://stackoverflow.com/questions/226302/where-can-i-look-up-the-definition-of-size-type-for-vectors-in-the-c-stl
// std::string is mutable: https://stackoverflow.com/questions/611263/efficient-string-concatenation-in-c
// friend; shadowing: https://stackoverflow.com/questions/4039817/friend-declaration-declares-a-non-template-function
// * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Making_New_Friends

// hashing: one-one mapping: (x == y) --> (h(x) == h(y))
// collision resolution: (x != y)

// ############################################
// [hash]

// https://www.modernescpp.com/index.php/hash-functions
// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
// https://stackoverflow.com/questions/8029121/how-to-hash-stdstring

// ############################################
// [collision resolution]: https://en.wikipedia.org/wiki/Hash_table 

// 1. SEPARATE CHAINING: hash table of linked lists
//  * on conflict, goes into the list (under the same hash index)
//  * desire uniformity of hash index, to keep lists small
//  * need to store key (for retrieval)
// performance: O(1) if m <= n;   (m/n)/2 if m > n, because on average, you search through half the list

// 2. PROBING: (open addressing)
//  * (linear probing): has hotspots, gradually becomes O(n)
//       add: if collision, increment index until free slot.   [linear scan; insert]
//       del: delete at location (creates a hole), then in all FOLLOWING locations 
//            (up to NoItem or entire array), DELETE AND REINSERT.   [linear scan; del-reinsert via linear scan]
//       search: linear scan 
//
// * (double hashing): like linear probing, but the jump step is determined by the 2nd hash func
//       add: similar to linear probing. can insert in slots marked "deleted"
//       del: can't actually remove items; can only flag them (slot state) as "deleted", and continue search
// https://www.geeksforgeeks.org/double-hashing/

// X. LINEAR HASHING: (never really learnt this one in COMP1927) - for dynamic resizing?
//  * http://delab.csd.auth.gr/papers/LinearHashing2017.pdf
//  * 2D structure: hash table of buckets (like linear chaining?)
//  * if a bucket overflows, then an overflow page is created for that bucket (i.e. extend the bucket)
//      BUT, there is also a cursor pointing to a 'current' bucket; it gets split in half
//      items in that one bucket are redistributed over the resulting two buckets
//  * cursor increments linearly, then loops back and restarts (loop i)
//      cursor behaviour has easy properties for generating a new hash, with minimal changes to table elem
//      previous hashing function h{i}; after cursor passes that slot, it uses h{i+1}
//  * cursor loop length expands only after completing original loop; doubles every loop completion


// ############################################
// (K -> *V): automatically gives you default NULL value

template<typename K, typename V>
class HT { // <-- (not worth implementing)
public: // bad practice
    std::vector<V> table;
    std::hash<K> hashbase; // use prime num, discrete math
    V defaultVal; // NoItem; or track a vector of keys

    HT(unsigned int n, std::hash<K> hashFunc, V defaultVal): table(n, defaultVal), defaultVal(defaultVal) { 
        this->hashbase = hashFunc; 
    }

    unsigned int hash(K k) { return hashbase(k) % table.size(); }

    void add(K k, V v) {
        table[hash(k)] = v; // basic idea (w/o collision handling)
        // (yeah, not worth implementing this...)
    }

    V del(K k) {
        V old = table[hash(k)];
        table[hash(k)] = defaultVal; // basic idea (w/o collision handling)
        return old;
    }
    
    V get(K k) {
        return table[hash(k)]; // basic idea (w/o collision handling)
    }

    // print/string function
    friend std::ostream& operator<<(std::ostream& out, const HT<K,V>& data) {
        out << *(data.table.begin());
        for (typename std::vector<V>::const_iterator elem = data.table.begin() +1; elem != data.table.end(); ++elem) { 
            out << " " << *elem; 
        }
        return out; // chaining
    }
};


// ########################################################
int main(int argc, char *argv[]) {
    // init
    std::hash<std::string> hash;
    HT<std::string, int> ht(5, hash, 0);
    ht.add("abc",1);
    ht.add("abcd",2);
    ht.add("fabcde",3);
    ht.del("fabcde");
    std::cout << "HT: " << ht << "  & get(abc):" << ht.get("abc") << "\n";
    // add-del operations
    //std::cout << hash("abcdef") << " % " << ht.table.size() <<  " = " << ht.hash("abcdef") << "\n";


    return 0;
}