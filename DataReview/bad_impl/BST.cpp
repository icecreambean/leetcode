#include <iostream>
#include <memory>
#include <queue>
#include <utility>
//#include <cmath>
// g++ -Wall -o bst BST.cpp

// CURRENT ISSUES (last update: 14 May 2020)
// * having issues with shared_ptr. any call from shared_from_this() will crash the program
//   https://en.cppreference.com/w/cpp/memory/enable_shared_from_this/shared_from_this


// https://softwareengineering.stackexchange.com/questions/56935/why-are-pointers-not-recommended-when-coding-with-c
// * totally forgot that smart pointers existed: (reference counting, and RAII)
// * avoid ptrs, because of smart ptrs + templated containers (e.g. std::vector<>) + RAII
// ...
// * std::unique_ptr: 1 ref to 1 object (also: std::move) 
// * std::shared_ptr: multiple ref to 1 object (reference counting)
// * std::weak_ptr  : multiple ref to 1 object, but OK to just ignore if already deallocated
// * regular ptrs   : useable in code that doesn't need to know about memory ownership, 
//                    because it won't allocate/deallocate or store anything past their execution
//    ^ (more info on when to use): see Herb Sutter CppCon 2016
//
// ptrs are a design pattern: Proxy Pattern: http://ootips.org/yonat/4dev/smart-pointers.html (old)
//  * C++ polymorphism: handled in generics by storing ptrs to base class, not the base class itself

// resetting a ptr: https://stackoverflow.com/questions/20195611/assigning-existing-values-to-smart-ptrs
// std::move ownership: https://stackoverflow.com/questions/26318506/transferring-the-ownership-of-object-from-one-unique-ptr-to-another-unique-ptr-i
//  * set to nullptr after std::move: https://stackoverflow.com/questions/36071220/what-happens-to-unique-ptr-after-stdmove
//  * seamless transfer unique_ptr to shared_ptr: https://www.nextptr.com/question/qa1257940863/converting-unique_ptr-to-shared_ptr-factory-function-example
//  * non-atomic transfer between 2 shared_ptr: https://stackoverflow.com/questions/41871115/why-would-i-stdmove-an-stdshared-ptr
// parameter passing: https://www.modernescpp.com/index.php/c-core-guidelines-passing-smart-pointer
//
// https://stackoverflow.com/questions/12051771/how-to-return-a-shared-ptr-of-this-to-the-object-that-owns-it
// https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
// https://stackoverflow.com/questions/17853212/using-shared-from-this-in-templated-classes
// can't go from shared to unique: https://stackoverflow.com/questions/37884728/does-c11-unique-ptr-and-shared-ptr-able-to-convert-to-each-others-type

// = default: https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration
// * compiler tricks to specify give default compiler implementation (or delete its generation)
// https://en.cppreference.com/w/cpp/language/rule_of_three

template<typename T>
class Tree: std::enable_shared_from_this<Tree<T>> { // root must be a shared_ptr
public:
    std::shared_ptr<T> root;
    std::shared_ptr<Tree<T>> left; // can't convert from: shared_ptr --> unique_ptr
    std::shared_ptr<Tree<T>> right;

    Tree() = default;
    void insert(T val);
    std::shared_ptr<Tree<T>> insertAtRoot(T val); // forces new elem to be the root node
    std::shared_ptr<Tree<T>> deleteNode(unsigned int index); // similar to rotation

    T find(T val); // binary search
    unsigned int depth(); // dfs
    unsigned int countNodes(); // dfs
    void print(); // bfs
    T get(unsigned int index); // dfs

    std::shared_ptr<Tree<T>> treePartition(); // makes existing elem as new root?
    std::shared_ptr<Tree<T>> rotateLeft();
    std::shared_ptr<Tree<T>> rotateRight();

    std::shared_ptr<Tree<T>> share() { return this->shared_from_this(); }
};

template<typename T>
void Tree<T>::insert(T val) {
    // base case
    if (root.get() == nullptr) {
        root = std::make_shared<T>(val); // allocates it for you
        return;
    }
    // left and right branches
    if (val < *root) {
        if (left.get() == nullptr) {
            left = std::make_shared<Tree<T>>();
        }
        left->insert(val); // recursion!!!
    } else {
        if (right.get() == nullptr) {
            right = std::make_shared<Tree<T>>();
        }
        right->insert(val);
    }
}

template<typename T>
void Tree<T>::print() {
    // empty; no transfer of ownership (only want to use it)
    // instead of using std::pair or std::tuple, create your own struct...
    struct qItem {
        Tree<T> *pCurRoot;
        int curLayer;
        unsigned int layerIndex;
    };

    int curLayer{-1};
    std::vector<std::vector<struct qItem>> layerNodes; // stores bfs result
    std::queue<struct qItem> queue;
    queue.push(qItem {this, 0, 1});
    //std::cout << "[Layer " << curLayer << "]:";
    while (!queue.empty()) {
        // current node
        struct qItem item = queue.front();
        queue.pop();
        if (item.curLayer > curLayer) {
            curLayer = item.curLayer;
            layerNodes.push_back(std::vector<struct qItem>());
            //std::cout << "\n[Layer " << curLayer << "]:";
        }
        if (item.pCurRoot == nullptr || item.pCurRoot->root.get() == nullptr) continue; // no neighbours
        layerNodes[item.curLayer].push_back(item);
        
        // append downward neighbours
        int nextLayer = item.curLayer + 1;
        unsigned int nextRightIndex = item.layerIndex * 2;
        queue.push(qItem {item.pCurRoot->left.get(), nextLayer, nextRightIndex-1});
        queue.push(qItem {item.pCurRoot->right.get(), nextLayer, nextRightIndex});
    }

    // read bfs results with correct padding
    unsigned int i = 0, n = 1;
    for (typename std::vector<std::vector<struct qItem>>::iterator iterLayer = layerNodes.begin(); iterLayer < layerNodes.end(); ++iterLayer) {
        unsigned int curIndex = 1;
        std::cout << "[Layer " << i << "]:";
        for (typename std::vector<struct qItem>::iterator iterNode = iterLayer->begin(); iterNode < iterLayer->end(); ++iterNode) {
            for (unsigned int j = curIndex; j < iterNode->layerIndex; ++j) std::cout << " n";
            std::cout << " " << *iterNode->pCurRoot->root;
            //std::cout << "(" << iterNode->layerIndex << ")"; // debug
            curIndex = iterNode->layerIndex + 1;
        }
        for (; curIndex <= n; ++curIndex) std::cout << " n";
        std::cout << "\n";
        ++i; n *= 2;
    }
    std::cout << "\n";
}

template<typename T>
std::shared_ptr<Tree<T>> Tree<T>::rotateLeft() { // OPERATIONS: redirect x2 (root); nullptr x2
                                                 // (see COMP1927): this is a bad impl; COMP1927 is just 2 ops (almost like a linked list)
    // cases in which it can't rotate
    if (root.get() == nullptr) {std::cout << "HEHE" << std::flush; return this->shared_from_this();}
    if (right == nullptr || right.get() == nullptr) return this->shared_from_this();
    // get leftmost/smallest in right branch
    Tree<T> *pPrev = this;
    Tree<T> *pCur = right.get();
    while (pCur->left != nullptr || pCur->left.get() != nullptr) {  // NOTE: unnecessarily overcomplicated rotation (see COMP1927)
        pPrev = pCur;
        pCur = pCur->left.get();
    }
    // prev->cur: replace cur with cur->right; (cur is floating)
    std::shared_ptr<Tree<T>> tempOwner = std::move(pPrev->left); // holds cur (prev->left = null)
    pPrev->left = std::move(pCur->right); // cur->right = null; cur->left = null (by default)
    //std::cout << "t1:\n"; print();
    // set cur as new root; (root is floating)
    // set: cur->left = root; cur->right = right; root->right = nullptr (automatic);
    pCur->right = std::move(this->right);
    //std::cout << "t2:\n"; print(); pCur->print();
    pCur->left = std::make_shared<Tree<int>>(*this); //this->shared_from_this(); 
    // ^ FIXME - huge ptr wrapping issue. horribly wrong. in this current impl, 2 shared_ptr point to same
    // resource without knowledge of one another.

    //std::cout << this->shared_from_this() << ", " << (this->shared_from_this() == nullptr) << "\n";
    //std::cout << "t3:\n"; pCur->print();
    return tempOwner;
}

// template<typename T>
// Tree<T> Tree<T>::rotateRight() {
//
// }


// ################################################
int main(int argc, char *argv[]) {
    //Tree<int> t(); // <-- thinks it's a function declaration
    std::shared_ptr<Tree<int>> t = std::make_shared<Tree<int>>();
    //std::cout << "simple case: " << std::flush << ((t->rotateLeft()) == nullptr) << "\n";
    t->insert(3); 
    t->insert(2);
    t->insert(8);
    t->insert(4);
    t->insert(6);
    t->insert(3);
    t->insert(1);
    t->print();
    // std::shared_ptr<Tree<int>> t2 = t->share();
    // t2->print();
    t = t->rotateLeft();
    //t = t->rotateLeft();
    std::cout << "final test:\n"; t->print();
    return 0;
}
