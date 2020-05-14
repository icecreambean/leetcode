#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
// https://en.cppreference.com/w/cpp/container/array

// https://stackoverflow.com/questions/10007986/c-pass-an-array-by-reference
// * clockwork spiral rule: some type reading 'trick'
// https://stackoverflow.com/questions/17156282/passing-a-stdarray-of-unknown-size-to-a-function

template<typename T,size_t N>
void printList(std::array<T,N>& a) {
    for (int e: a) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}

template<typename T> 
void swap(T& v1 ,T& v2) {
    T tmp = v1;
    v1 = v2;
    v2 = tmp;
}

template<typename T,size_t N>
void selectionSort(std::array<T,N>a, bool (*cmp)(T,T)) { // std::array<T,N>&a  to directly modify
    std::cout << "select: ";
    for (int i = 0; i < static_cast<int>(a.size()); i++) {
        // [get min value]
        typename std::array<T,N>::iterator minVal = std::min_element(a.begin() + i, a.end(), cmp);
        int minIndex = static_cast<int>(std::distance(a.begin(), minVal));
        //std::cout << *minVal << "," << i << "," << minIndex << "\n";
        // [swap]
        swap(a[i], a[minIndex]);
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
};

template<typename T, size_t N>
void insertionSort(std::array<T,N> a, bool (*cmp)(T,T)) {
    // unstable impl, as cmp doesn't stop on first occurrence of "="
    std::cout << "Insert: ";
    for (int i = 1; i < static_cast<int>(a.size()); i++) {
        T insertVal = a[i];
        // find first cmp occurrence where a[j-1] < a[i]
        // hence, we move a[i] to a[j] s.t. a[j-1] < a[j] maintained
        for (int j = i; j >= 0; j--) {
            if (j == 0 || cmp(a[j-1], insertVal)) {
                //std::cout << "{" << j << "}";
                a[j] = insertVal;
                break;
            }
            // [bubble the current element down]
            a[j] = a[j-1];
        }
        //printList(a);
    }
    printList(a);
}

// sees entire list every iteration with ordered comparison (relative) 
template<typename T, size_t N>
void bubbleSort(std::array<T,N> a, bool (*cmp)(T,T)) {
    std::cout << "Bubble: ";
    for (int i = static_cast<int>(a.size())-1, n = 1; i > 0; i--, n++) { // propagates sorted elems to end of list
        bool isSwap = false;
        for (int j = 0; j < i; j++) {
            if (!(cmp(a[j], a[j+1]))) {
                swap(a[j], a[j+1]);
                isSwap = true;
            }
        }
        if (!isSwap) {
            //std::cout << "(Stopped after " << n << "/" << static_cast<int>(a.size())-1 << " iter)\n";
            break;
        }
    }
    printList(a);
    //std::cout << "\n";
}

// #######################################

// quicksort median of three: 
// https://www.java-tips.org/java-se-tips-100019/24-java-lang/1896-quick-sort-implementation-with-median-of-three-partitioning-and-cutoff-for-small-arrays.html
// https://stackoverflow.com/questions/7559608/median-of-three-values-strategy
template<typename T, size_t N>
int medianOfThree(std::array<T,N>& a, bool (*cmp)(T,T), int lo, int hi) {
    // sort lo, mid, hi to remove occurrence of worst case manipulation
    int mid = lo+(hi-lo)/2;
    if (cmp(a[mid],a[lo])) swap(a[lo], a[mid]);
    if (cmp(a[hi],a[mid])) swap(a[mid], a[hi]);
    if (cmp(a[mid], a[lo])) swap(a[lo], a[mid]);
    return mid;
}
// have to return new position of pivot, as the pivot will move to its right place
// NOTE: Wikipedia implem does nearly the same thing as below and is more efficient, but harder
//       to understand. It works because it includes the pivot value in subsequent partitions
template<typename T, size_t N>
int qpartition(std::array<T,N>& a, bool (*cmp)(T,T), int lo, int hi, int pivot) {
    while (true) {
        // skip duplicate values (to the pivot value), UP to trying to pass the pivot
        // (cursor movement limited up to (capturing the) pivot)
        while (!cmp(a[pivot], a[lo]) && lo < pivot) lo++;
        while (!cmp(a[hi], a[pivot]) && hi > pivot) hi--;
        
        if (lo >= pivot && hi <= pivot) break;
        else if (lo == pivot) pivot = hi; // this is where the pivot will end up
        else if (hi == pivot) pivot = lo; // (pivot has been captured by a cursor)
        swap(a[lo], a[hi]);
    }
    return pivot; // have to account for the pivot value moving
}
// avg: O(n log n)
// worst: O(n^2): bad pivot selection
// not stable
template<typename T, size_t N> // hi: inclusive
void quickSort(std::array<T,N>& a, bool (*cmp)(T,T), int lo, int hi) { // recursion implem
    // (should check if already sorted?)
    if (hi <= lo) return;
    int pivot = medianOfThree(a, cmp, lo, hi);
    pivot = qpartition(a, cmp, lo, hi, pivot);
    //std::cout << "pivot(" << pivot << "): "; printList(a);
    quickSort(a, cmp, lo, pivot-1);
    quickSort(a, cmp, pivot+1, hi);
    // basically a whacky bubble-sort (end of iteration: 1 element is correctly placed,
    // except it's at the pivot position, not at the end of the list)
}


template<typename T, size_t N> // hi (inclusive)
void mergeSort(std::array<T,N>& a, bool (*cmp)(T,T), int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo+(hi-lo)/2;
    mergeSort(a, cmp, lo, mid);
    mergeSort(a, cmp, mid+1, hi);

    // combine sorted sub-lists: can't do swaps without breaking sorted sub-list constraint
    //std::array<T,hi-lo+1> tmp; // not valid, N must be a const expression
    std::vector<T> tmp(hi-lo+1); // can't .push_back() if init allocated already
    int tmpCursor = 0;
    int leftCursor = lo;
    int rightCursor = mid+1;
    while (leftCursor <= mid && rightCursor <= hi) {
        // std::cout << "(" << a[leftCursor] << "," << a[rightCursor] << "->" << 
        //     ((cmp(a[leftCursor], a[rightCursor])) ? a[leftCursor] : a[rightCursor]) << ") ";
        tmp[tmpCursor++] = ((cmp(a[leftCursor], a[rightCursor])) ? a[leftCursor++] : a[rightCursor++]);
    }
    // ** copy contents of unfinished list
    while (leftCursor <= mid) tmp[tmpCursor++] = (a[leftCursor++]);
    while (rightCursor <= hi) tmp[tmpCursor++] = (a[rightCursor++]);
    // ** copy tmp contents back to original list
    // for (T e: tmp) std::cout << e << " "; 
    // std::cout << "\n";
    for (int i = lo; i <= hi; i++) a[i] = tmp[i-lo];
    //printList(a);
}


// template<typename T, size_t N>
// void insertionSort(std::array<T,N> a, bool (*cmp)(T,T)) {
//     std::cout << "Insertion: ";
//     for (int i = 0; i < static_cast<int>(a.size()); i++) {
//
//     }
//     std::cout << "\n";
// }

// #######################################

// heapSort: insert into heap, then pop out of heap. O(n log n); not stable; in-place
// * log n per insertion/deletion. Perform n insertions.

// #######################################
// not strictly necessary if operator< and others have already been overloaded for type T
bool intCmp(int v1, int v2) { return v1 < v2; }

int main(int argc, char *argv[]) {
    std::array<int,8> a{{5,4,2,8,6,1,7,3}};

    selectionSort(a, intCmp);
    insertionSort(a, intCmp);
    bubbleSort(a, intCmp);
    std::cout << "Origin: "; printList(a); std::cout << "\n";
    
    //std::array<int,8> b{{1,1,1,1,1,1,1,1}};
    //std::array<int,8> b = a;
    std::array<int,10> b{{5,4,8,1,5,2,3,7,1,6}};
    std::array<int,10> c = b;
    std::cout << "Origi2: "; printList(b);

    quickSort(b, intCmp, 0, b.size()-1);
    std::cout << "Quick : "; printList(b);
    
    mergeSort(c, intCmp, 0, c.size()-1);
    std::cout << "Merge : "; printList(c);

    return 0;
}