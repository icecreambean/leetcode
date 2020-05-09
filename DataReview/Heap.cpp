#include <iostream>
#include <cstring> // bad practice for memcpy?

// https://stackoverflow.com/questions/4670782/the-difference-between-delete-and-delete-in-c
// https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
// * "Rule of Three": need copy constructor+assignment, to do deepcopy on pointer items
// https://stackoverflow.com/questions/16137953/is-there-a-function-to-copy-an-array-in-c-c
// * std::copy()

// Strategy pattern: https://www.cprogramming.com/tutorial/function-pointers.html

//##########################################################
// .hpp header file
//  "a class template is not a class, it's a recipe for creating a new class for each T we encounter"
template<typename T>
class Heap {
public: // private by default; bad style (just using for debugging)
    T *array; // too C-style; could use std::array or std::vector
    int totalSize; // uniform initialisation syntax
    int curSize{0};
    int (*cmp)(T,T); // assume written as min-heap
    T invalidVal;

public:
    // 1. member initialisation list
    Heap(unsigned int size, int (*cmp)(T,T), T invalidVal): totalSize(size) { // must be done inside class
        array = new T[size];
        this->cmp = cmp;
        this->invalidVal = invalidVal;
    }
    
    // 2. copy constructor
    Heap(const Heap& that): totalSize(that.totalSize), curSize(that.curSize) {
        // can't use std::copy(); it requires an iterator
        array = new T[that.totalSize];
        std::memcpy(array, that.array, that.totalSize*sizeof(T));
        cmp = that.cmp;
        invalidVal = that.invalidVal;
        //std::cout << "[copy constructor]: bytes copied: " << that.totalSize*sizeof(T) << "\n";
    }

    // 2. copy assignment
    // https://stackoverflow.com/questions/3105798/why-must-the-copy-assignment-operator-return-a-reference-const-reference
    // https://stackoverflow.com/questions/2649068/has-anyone-found-the-need-to-declare-the-return-parameter-of-a-copy-assignment-op
    // * compiler reasoning
    Heap& operator=(const Heap& that) {
        if (this != &that) {
            //~Heap(); // can't do this - this will end the lifetime of the object
            delete[] array;
            array = new T[that.totalSize];
            std::memcpy(array, that.array, that.totalSize*sizeof(T));
            //std::cout << "[copy assignment]: bytes copied: " << that.totalSize*sizeof(T) << "\n";
            totalSize = that.totalSize;
            curSize = that.curSize;
            cmp = that.cmp;
            invalidVal = that.invalidVal;
        }
        return *this; // if &this == &that, then no changes were required
        // `this` is a ptr: https://www.geeksforgeeks.org/this-pointer-in-c/
        // `that` is a reference...
    }

    // 3. destructor
    ~Heap() {
        delete[] array;
    }

    void printHeap();
    void insert(T val);
    T pop();
private:
    void fixUp(T k);
};

//##########################################################
// .cpp or .tpp implementation file
// https://stackoverflow.com/questions/15283195/argument-list-for-class-template-is-missing
template<typename T>
void Heap<T>::printHeap() {
    for (int i = 0; i < curSize; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

template<typename T>
void Heap<T>::insert(T val) {
    // insert in last location of array, and then correct upwards
    // by comparing relative to the parent

    if (curSize >= totalSize) return;
    // NOTE: should do cmp() safety checks (could be null)...

    int k = curSize; // unnecessary
    array[curSize++] = val;
    fixUp(k);
}

template<typename T>
void Heap<T>::fixUp(T k) { // index
    while (k > 0) { // tree root
        // (k+1)/2-1 = (k-1)/2
        int rootIndex = (k-1)/2;
        //std::cout << "  b:" << array[rootIndex] << "->" << array[k] << "\n";
        if (cmp(array[rootIndex], array[k]) > 0) {
            T tmp = array[k];
            array[k] = array[rootIndex];
            array[rootIndex] = tmp;
        }
        //std::cout << "  a:" << array[rootIndex] << "->" << array[k] << "\n";
        k = rootIndex;
    }
}

template<typename T>
T Heap<T>::pop() {
    // remove root, and fix downwards (promoting new root)
    // this can create a hole in the array; 
    if (curSize <= 0) return invalidVal;
    T result = array[0];
    //std:: cout << "\n"; 

    int parentIndex = 0;
    while (parentIndex*2+1 < curSize) {
        // (p+1) * 2 -1 = p*2 +1 --> very confusing
        int nextIndex = parentIndex * 2 + 1;
        if (nextIndex+1 < curSize && cmp(array[nextIndex], array[nextIndex+1]) > 0) {
            nextIndex++; // right child exists and is larger
        }
        //std::cout << "  * " << parentIndex << "->" << nextIndex << "\n";
        array[parentIndex] = array[nextIndex];
        //printHeap(); std::cout << "  ^ (p,n): " << parentIndex << "," << nextIndex << "\n";
        parentIndex = nextIndex;
    }
    //printHeap(); std::cout << "  ^ leaf: " << parentIndex << "\n";
    curSize--;
    //std::cout << "(" << curSize << ")";
    if (parentIndex < curSize) {
        //std::cout << "{" << parentIndex << "," << array[curSize] << "}";
        array[parentIndex] = array[curSize]; // fix up the remaining hole
        fixUp(parentIndex);
    }
    
    return result;
}


//##########################################################
int intcmp(int v1, int v2) { return v1-v2; }
int intcmpmax(int v1, int v2) { return v2-v1; }

// separate program
int main(int argc, char *argv[]) {
    // https://stackoverflow.com/questions/1461432/what-is-array-to-pointer-decay
    //int a[10];
    //std::cout << "Hellow World: " << sizeof(a) << "!\n"; // 40 bytes

    // Heap<int> h1(10, intcmp, -1);
    // h1.insert(5); h1.printHeap();
    // h1.insert(2); h1.printHeap();
    // h1.insert(7); h1.printHeap();
    // Heap<int> h2(h1);

    // //Heap<int> h3 = h1;  // compiles down to a copy constructor
    // Heap<int> h3(20, intcmp, -1);
    // h3.insert(100);
    // h3 = h1;

    // h2.insert(10);
    // h3.insert(11);
    // std::cout << "h1: (" << h1.curSize << ") "; h1.printHeap();
    // std::cout << "h2: (" << h2.curSize << ") "; h2.printHeap();
    // std::cout << "h3: (" << h3.curSize << ") "; h3.printHeap();

    // std::cout << "\n[TEST 2]:\n";
    // std::cout << "h1 pop(" << h1.pop() << "): "; h1.printHeap();

    // #############
    // Heap<int> h4(16, intcmpmax, -1);
    // h4.insert(5);
    // h4.insert(8);
    // h4.insert(1);
    // h4.insert(3);
    // h4.insert(7);
    // h4.insert(2);
    // h4.insert(4);
    // h4.insert(6);
    // h4.insert(6);

    // std::cout << "[" << h4.curSize << "]: "; h4.printHeap();
    // while (h4.curSize > 0) {
    //     std::cout << "[" << h4.curSize << "]: " << h4.pop() << "; "; h4.printHeap();
    // }
    
    // #############
    Heap<int> h5(16, intcmpmax, -1);
    int v5[] = {60,50,40,3,2,1,10};
    for (int i = 0; i < static_cast<int>(sizeof(v5)/sizeof(int)); i++) h5.insert(v5[i]);
    h5.printHeap();
    while (h5.curSize > 0) {
        std::cout << "[" << h5.curSize << "]: " << h5.pop() << "; "; h5.printHeap();
    }


    return 0;
}