# Containers (lists, trees, HTs)

<https://en.cppreference.com/w/cpp/container>
<https://embeddedartistry.com/blog/2017/08/02/an-overview-of-c-stl-containers/>
 * Scope-Bound Resource Management (SBRM) --> means RAII

<https://embeddedartistry.com/blog/2017/07/26/stdstring-vs-c-strings>
 * std::string: operator overloading; .append(); .reserve(N) - preallocation, 
   .size(); .capacity(); .empty(); .clear(); .insert() - idx; .replace() - substr; 
   .push_back(); .pop_back(); .erase(); .substr(); .find().
   Automated, dynamic allocation (unlike compile-time C-strings)
 * std::string_view: C++/17; avoids copying already owned data; non-owning.
   Designed to be as efficient as compile-time C-strings. 
   std::array - templated wrapper for C-arrays.
   [Embedded applications are mostly interested in forcing static memory allocations]

3 container categories + 1 wrapper category: (as defined in C++ standard)

**Container adapters**: restricted interfaces/wrappers around containers
 * Adaptor pattern => wrapper: wrapped interface for another interface
 * `stack<T, Container=deque<T>>`; queue; 
   `priority_queue<T, Container=vector<T>, less<Container::value_type>` - heap

**Sequence containers**: same type; linear sequence
 * array (static), vector (dynamic), forward_list (singly-linked), list (doubly-linked), 
   deque (doubly-ended queue). std::string also counts, but generally not included.

**Associative containers**: sorted, fast look-up O(logN)
 * Red-black trees (4 insert cases, 6 delete cases), in most standards
 * **Unique keys**: set - sorted keys, 
   `map<K, T, Compare=less<K>, Allocator=allocator<pair<K,T>>>` - (k,v) sorted by key.
 * **Duplicate keys allowed**: multiset, multimap

**Unordered associative containers**:
 * HT: unsorted; accessed via hash. O(n) worst case. Only checks equal; **doesn't compare**.
 * **Unique keys**: `unordered_set<K, T, KeyEqual=equal_to<K>, Allocator=allocator<K>>`,
   unordered_map
 * **Duplicate keys allowed**: unordered_multiset, unordered_multimap

Multiset, multimap: use .find() to get an iterator; no convenience operator[].

Container thread safety:
 * Separate unshared instances of containers are thread-safe
 * Edge cases: const member functions (or read-only functions) "thread-safe"; 
   different elements in same container can be modified concurrently, 
   except for `vector<bool>`, etc.
 * **If there are a write thread and several read threads, protection required**
 * Locks, etc. Boost library - evolves faster than the standard

<https://stackoverflow.com/questions/3265266/hash-tables-v-self-balancing-search-trees>
 * Prefer tree to HT when: expensive hash, ordering required, better worst-case performance
 * Trees vs HT: dynamic vs static array; O(logN) vs O(1) in average-case performance
 * Java implementation of HashMap leverages benefits of both
 * KISS: theoretical performance needs to be compared to practical memory implementation

`vector<bool>`: dynamically allocated bitset
 * C++/98 design mistake (violated design principles; loss of standardised container 
   interface functionality). Returns proxy reference objects instead of true references.
 * <https://stackoverflow.com/questions/670308/alternative-to-vectorbool>


## HT Usage

<https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key>
 * Standard types don't need to specify a hash function
 * Custom classes need a custom hash function. Typical strategy: `hash<T>()(T member)` 
   individual members and XOR + bitshift results together. (See link!!)


## Deque vs list

<https://stackoverflow.com/questions/1436020/whats-the-difference-between-deque-and-list-stl-containers>

Deque: 
 * Implemented as a vector of (ptrs to) vectors: 
   <https://stackoverflow.com/questions/6292332/what-really-is-a-deque-in-stl>
 * Insert/remove is amortised O(1) at beginning and end of sequence, otherwise O(n) 
   because of shuffling (would have to occur across buckets/chunks).
 * Outer vector: on realloc, splits empty space to equal parts beginning and end of vector.
   Outer vector pointer shuffling is faster (due to fewer elements).
 * Inner vector: begin ptr (insert from end to start of vector); end ptr (normal op.)

List: (non-contiguous memory allocation)
 * Implemented as a linked list
 * Insert/remove is amortised O(1) at beginning/end/middle of sequence. (Why middle??)
 * Insertion and splicing do not invalidate iterators to list elements. Iterators are
   updated to follow correct linking; only iterators to removed elements are invalidated.
 * Splicing: can transfer nodes from one list to another without moving/copying memory

Use case consideration: how often do you need to insert/remove in the middle?

<https://baptiste-wicht.com/posts/2012/12/cpp-benchmark-vector-list-deque.html>
 * List: slow to iterate; poor spatial locality; handles large elements well
 * Vector/deque: faster than list on very small data; bad if high-cost copy-assignment
   (due to shuffling of elements). Deque better than vector for random insertions.

Deque vs vector:
 * Performance of insert/delete at **end** for vector is better than deque.
 * No iterator invalidation happens in deque for insert/delete at front/end

<https://embeddedartistry.com/blog/2017/09/11/choosing-the-right-container-sequential-containers/> - see "general rules of thumb"
 * Use vector as default over C-arrays
 * Prefer deque to vector if inserting at both front and back
 * Prefer list if lots of inserts in middle of list, and random access not required
 * Prefer vector over list if you are using a cache
Memory considerations:
 * Vector: contiguous; compatible with C-array APIs. Safest in cache performance
 * Deque: allocation by chunks
 * List: allocation by nodes

## Allocator

<https://en.wikipedia.org/wiki/Allocator_(C%2B%2B)>

Handles allocation/deallocation of memory for a given container.
Gives the programmer control over memory allocation within containers

<https://en.cppreference.com/w/cpp/memory/allocator>
 * Default Allocator used by all standard library containers if no user-specified 
   allocator is provided. Stateless => is interchangeable

# Const

<http://duramecho.com/ComputerInformation/WhyHowCppConst.html>
Positioning of const in ptr syntax:
 * `[T] const [T]*`: var ptr(const T)
 * `T * const`: const ptr(var T)
 * `[T] const [T]* const`: const ptr(const T)
`const T*` **return type**:
 * Unalterable contents (e.g. const strings) detected at compile time
`const T&` **input arguments**:
 * More efficient (reduces copying). const for safety guarantees
 * Messy, because the programmer has to explicitly manage `in/out/inout` conditions

`int classMethod(int args) const { ... }` - member variables are read-only within method.
 * Implied as `const Class* this`

JOKE: `const int*const Method3(const int*const&)const;`

`mutable` is a design violation of `const` (i.e. overrides). 
 * Usage: to store intermediate calculations to be reused in future method calls

`const` is **infectious**:
 * `const &` objects can only use their const methods

`const_cast` is a design violation of `const`: removes const.


# Cpp vs C in embedded

<https://embeddedartistry.com/blog/2016/07/22/embedded-c-whats-the-value/>
 * Type safety: typecasts, nullptr, templates (avoids void*), pass-by-reference, const
 * Function overloading
 * Compiler niceness; templates (only uses what is required at compile time)
 * Smart pointers; RAII (applies to files, locks)

 * std libraries for aligning memory
 * customise allocators/deleters
 * Virtual functions/classes: 1 vtable/class; 1 ptr/object (1 deference/call).
   Interfaces, polymorphism.
 * (Even std::array is apparently nice to have).
 * (Implementations in C --> already handled by C++ compiler).


## Embedded Design Patterns

<https://embeddedartistry.com/fieldatlas/design-pattern-catalogue/>