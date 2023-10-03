#ifndef __MYQSORT_HPP__
#define __MYQSORT_HPP__

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template<typename T,typename Compare=std::less<T>> 
class MyQsort { 

public:     
    MyQsort(T *arr, size_t size, Compare com);     
    void quick(int left, int right, Compare &com);     
    int partition(int left, int right, Compare &com);     
    void print(); 

private:    
    vector<T> _vec; 
};

template<typename T, typename Compare> 
MyQsort<T, Compare>::MyQsort(T *arr, size_t size, Compare com) 
: _vec(arr, arr+size) {

    quick(0, size-1, com);
    print();
}


template<typename T, typename Compare> 
void MyQsort<T, Compare>::quick(int left, int right, Compare &com) {

    if (left >= right) {
        return ;
    }

    int index = partition(left, right, com);

    quick(left, index-1, com);
    quick(index+1, right, com);
}



template<typename T, typename Compare> 
int MyQsort<T, Compare>::partition(int left, int right, Compare &com) {

    T basic = _vec[right];

    int lt = left;
    int rt = right;
    
    while (lt <= rt) {
        while (lt < rt && com(_vec[lt], basic)) {
            ++lt;
        }

        if (lt == rt) {
            _vec[lt] = basic;
            break;
        } else {
            _vec[rt--] = _vec[lt];
        }

        while (lt < rt && com(basic, _vec[rt])) {
            --rt;
        }

        if (lt == rt) {
            _vec[lt] = basic;
            break;
        } else {
            _vec[lt++] = _vec[rt];
        }
    }

    return lt;
}


template<typename T, typename Compare> 
void MyQsort<T, Compare>::print() {

    for (auto& elem : _vec) {
        cout << elem << " ";
    }
    cout << endl;
}



#endif