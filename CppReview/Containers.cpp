// [AGENDA]:
// * investigate compare function for trees (map)
// * investigate hash functions for hash tables (unordered_map)

// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
// https://codegolf.stackexchange.com/questions/1956/generate-the-longest-error-message-in-c
// https://softwareengineering.stackexchange.com/questions/70086/why-are-c-template-error-messages-so-horrific

// https://en.cppreference.com/w/cpp/header
// * each container in its own separate library
// * <algorithm> - a bunch of basic/typical functionality

// https://stackoverflow.com/questions/52236209/difference-between-make-pair-and-curly-brackets-for-assigning-a-pair-in-c
// * aggregate initialisation: brace-enclosed initializer lists to initialize all 
//   members of an aggregate. Implemented using typename value_type

// https://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap-and-put-them-into-a-vector
// * to get the vectors of a map's keys, need to iterate and get .first from each pair

// use typedef to abstract long type names

// g++ -Wall -std=c++17 -o test Containers.cpp
#include <iostream>
#include <unordered_map>
#include <map>
#include <cmath>
// https://stackoverflow.com/questions/15595804/c-hash-function-for-string-in-unordered-map/18005072
// * good practice to do `#include <string>` if using it as a key in unordered_map

// ########################################
class Person {
private:
    std::string name;
    int age;
public:
    Person(std::string name, int age): name(name), age(age) {};

    // [NOT NEEDED]: added in for documentation/practice only
    Person(const Person &p): name(p.name), age(p.age) {}; // copy constructor
    Person& operator=(const Person& p) { // copy assignment
        if (&p == this) return *this; // 1. check self-assignment (optional?)
        name = p.name; age = p.age; // 2. copy contents
        return *this;
    }

    // [NEEDED FOR HASH TABLE keys]: equality operator
    //bool operator== (const Person& p) const { return name == p.name && age == p.age; }
    friend bool operator== (const Person& lhs, const Person& rhs);
    // * both options for operator== work, but friend impl is more powerful
    // * (overriden functions must match EXACTLY, else cryptic template errors)

    std::string getName() const { return name; }
    int getAge() const { return age; }
};
// https://en.cppreference.com/w/cpp/language/rule_of_three
// https://en.cppreference.com/w/cpp/language/copy_assignment

// https://stackoverflow.com/questions/3850058/friend-in-operator-or-when-should-i-use-it
// * friend impl more powerful: as a non-member function, flexibility of comparing 
//   any two types that can cast into your arguments
bool operator== (const Person& lhs, const Person& rhs) { 
    return lhs.name == rhs.name && lhs.age == rhs.age; 
}

// https://en.cppreference.com/w/cpp/utility/hash
// * standard requires a struct with overriden operator()()
// * noexcept: method will not throw exceptions (compile-time check)
// https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes
// 1. apply bitshifting first to minimise identical values XORing into 0
//    shift-and-add => multiply(pow2) and add
// 2. XOR preserves random distributions. Still generally a poor way of combining hashes
//    due to commutativity. `m * H(A) + H(B)` for large odd m is better.
// * boost::hash_combine(): has a seed constant to break symmetry, introduce noise.
//   you should use this to join together hash combinations.
//
// https://gist.github.com/beyondwdq/7245893
// - this is a struct impersonating a function, through operator()
// - required for defining generics then by using function pointers?
// - (function pointers still widely used in C++ for callbacks?)
struct PersonHash {
    std::size_t operator()(Person const &p) const noexcept {
        std::size_t h1 = std::hash<std::string>{}(p.getName());
        std::size_t h2 = std::hash<int>{}(p.getAge());
        return h1 ^ (h2 << 1);
    }
};
// std::hash<std::string>{}(p.getName()) - create hash instance, 
// and use as function immediately

// [ALT]: add your generic hash<> to the std namespace
namespace std {
    template<> // require hash<> to be template, but type enforced as Person
    struct hash<Person> { // basically copy-paste identical
        std::size_t operator()(Person const &p) const noexcept {
            std::size_t h1 = std::hash<std::string>{}(p.getName()); // identical
            std::size_t h2 = std::hash<int>{}(p.getAge());
            return h1 ^ (h2 << 1);
        }
    };
}

// defn of operator< not strictly required; custom std::less implementations
struct PersonCompare {
    bool operator()(Person const& p1, Person const& p2) const noexcept{
        return p1.getAge() >= p2.getAge();
    }
};

struct PersonCompare42 {
    bool operator()(Person const& p1, Person const& p2) const noexcept{
        return std::abs(p1.getAge()-42) < std::abs(p2.getAge()-42);
    }
};
// https://www.fluentcpp.com/2019/10/29/stdless-and-its-modern-evolution/


// [HASH TABLES] ########################################
// https://en.cppreference.com/w/cpp/container/unordered_map/erase
// * .erase(K) or .erase(iterator)

void ht1() {
    // std::hash<Key>; init list of std::pair<K,T>
    std::unordered_map<std::string, int> ages { 
        {"george", 24}
    };
    // ages.insert("netero", "100"); // DOES NOT EXIST!!
    ages.insert(std::make_pair("arthur", 50));
    ages.insert({"harold", 16});
    ages.insert_or_assign("george", 42); // C++17

    // [ITERATOR]: treat as pointers (to pairs); could use auto
    //for (std::unordered_map<std::string, int>::iterator p = ages.begin(); p != ages.end(); p++) {
    for (auto p = ages.begin(); p != ages.end(); p++) {
        std::cout << "name: " << p->first << ", age: " << p->second << "\n";
    }

    // [FOREACH]: pairs
    //for (std::pair<std::string, int> p: ages) {
    for (auto &p: ages) {    
        std::cout << "NAME: " << p.first << ", AGE: " << p.second << "\n";
    }

    std::cout << "george's age: " << ages["george"] << "\n";
    std::cout << "\n";
}

void ht2() {
    //std::unordered_map<Person, std::string> descriptions; // uses std::hash
    std::unordered_map<Person, std::string, PersonHash> descriptions; // uses custom hash
    Person p1{"victor", 50};
    Person p2{"charlie", 24};
    Person p3{"nathan", 75};

    descriptions.insert({p1, "cool"});
    descriptions.insert({p2, "noob"});
    descriptions.insert({p3, "master"});
    descriptions.erase(p2);

    for (auto &p: descriptions) {
        std::cout << p.first.getName() << ": " << p.first.getAge() << ", " << p.second << "\n";
    }
    std::cout << "\n";
}

// [TREES] ########################################
// * KEY: instead of providing a custom hash, provide a comparator: std::less
// * sorted keys

// https://stackoverflow.com/questions/2699060/how-can-i-sort-an-stl-map-by-value
// * can't sort by values. if this is required, use a set instead of a map

void tree1() {
    std::map<std::string, int> ages { 
        {"george", 42}, {"harold", 16}, {"arthur", 50}
    };

    for (auto p: ages) { // results are sorted by key (string)
        std::cout << "name: " << p.first << ", age: " << p.second << "\n";
    }
    std::cout << "\n";
}

void tree2() {
    Person p1{"victor", 50};
    Person p2{"charlie", 14};
    Person p3{"nathan", 75};
    std::map<Person, std::string, PersonCompare> descriptions { // oldest --> youngest
    //std::map<Person, std::string, PersonCompare42> descriptions { // 50,14,75
        {p1, "cool"}, {p3, "master"}, {p2, "noob"} // insert order: 50,75,14
    };

    for (auto &p: descriptions) { // results ordered by `less` - oldest to youngest
        std::cout << p.first.getName() << ": " << p.first.getAge() << ", " << p.second << "\n";
    }
    std::cout << "\n";
}

// ########################################
int main(int argc, char *argv[]) {
    ht1();
    ht2();
    tree1();
    tree2();
    return 0;
}