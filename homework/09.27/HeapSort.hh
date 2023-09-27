#ifndef __HEAPSORT_HPP__
#define __HEAPSORT_HPP__


#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

using std::vector;
using std::cout;
using std::endl;


template <typename T> 
void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template <typename T, typename Compare = std::less<T>> 
class HeapSort { 

public:  
    HeapSort(T *arr, size_t size, Compare com);  
    void heapAdjust(size_t, size_t, Compare &com);  
    void sort(Compare &com);  
    void print();

private:  
    vector<T> _vec; 
};

template <typename T, typename Compare> 
HeapSort<T, Compare>::HeapSort(T *arr, size_t size, Compare com) 
: _vec(arr, arr+size) { 

    print();

    sort(com);

    print();
}

template <typename T, typename Compare> 
void HeapSort<T, Compare>::heapAdjust(size_t left, size_t right, Compare &com) {

    while (left < right) {
        size_t lchild = 2 * left + 1;
        size_t rchild = 2 * left + 2;

        size_t index = left;

        if (lchild < right && com(_vec[index], _vec[lchild])) {
            index = lchild;
        }

        if (rchild < right && com(_vec[index], _vec[rchild])) {
            index = rchild;
        }

        if (index == left) {
            break;
        }

        swap(_vec[index], _vec[left]);

        left = index;
    }
}

template <typename T, typename Compare> 
void HeapSort<T, Compare>::sort(Compare &com) {
    
    for (int i = (_vec.size() - 2) / 2; i >= 0; --i) {
        heapAdjust(i, _vec.size(), com);
    }

    int len = _vec.size();

    while (len > 1) {
        swap(_vec[0], _vec[len - 1]);
        --len;

        heapAdjust(0, len, com);
    }
}


template <typename T, typename Compare> 
void HeapSort<T, Compare>::print() {

    for (auto& elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}

#endif