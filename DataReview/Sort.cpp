#include <iostream>
#include <array>
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
};

template<typename T> 
void swap(T& v1 ,T& v2) {
    T tmp = v1;
    v1 = v2;
    v2 = tmp;
};

template<typename T,size_t N>
void selectionSort(std::array<T,N>a, bool (*cmp)(T,T)) { // std::array<T,N>&a  to directly modify
    std::cout << "select: ";
    for (int i = 0; i < a.size(); i++) {
        // get min value
        typename std::array<T,N>::iterator minVal = std::min_element(a.begin() + i, a.end(), cmp);
        int minIndex = static_cast<int>(std::distance(a.begin(), minVal));
        //std::cout << *minVal << "," << i << "," << minIndex << "\n";
        // swap
        swap(a[i], a[minIndex]);
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
};

template<typename T, size_t N>
void insertionSort(std::array<T,N> a, bool (*cmp)(T,T)) {
    // unstable impl, as cmp doesn't stop on first occurrence of "="
    std::cout << "Insert: ";
    for (int i = 1; i < a.size(); i++) {
        T insertVal = a[i];
        // find first cmp occurrence where a[j-1] < a[i]
        // hence, we move a[i] to a[j] s.t. a[j-1] < a[j] maintained
        for (int j = i; j >= 0; j--) {
            if (j == 0 || cmp(a[j-1], insertVal)) {
                //std::cout << "{" << j << "}";
                a[j] = insertVal;
                break;
            }
            // bubble down
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
    for (int i = a.size()-1, n = 1; i > 0; i--, n++) { // propagates sorted elems to end of list
        bool isSwap = false;
        for (int j = 0; j < i; j++) {
            if (!(cmp(a[j], a[j+1]))) {
                swap(a[j], a[j+1]);
                isSwap = true;
            }
        }
        if (!isSwap) {
            //std::cout << "(Stopped after " << n << "/" << a.size()-1 << " iter)\n";
            break;
        }
    }
    printList(a);
    std::cout << "\n";
}

// #######################################


// template<typename T, size_t N>
// void insertionSort(std::array<T,N> a, bool (*cmp)(T,T)) {
//     std::cout << "Insertion: ";
//     for (int i = 0; i < a.size(); i++) {

//     }
//     std::cout << "\n";
// }

// #######################################
bool intCmp(int v1, int v2) { return v1 < v2; }

int main(int argc, char *argv[]) {
    std::array<int,8> a{{5,4,2,8,6,1,7,3}};

    selectionSort(a, intCmp);
    insertionSort(a, intCmp);
    bubbleSort(a, intCmp);

    std::cout << "Original: ";
    printList(a);
    return 0;
}