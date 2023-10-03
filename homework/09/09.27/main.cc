#include "HeapSort.hh"
#include <functional>
#include <iostream>


// 函数对象
struct CompareIntReverse {
    bool operator()(const int& v1, const int& v2) {
        return v1 > v2;
    }
};

int main(int argc, char* argv[]) {

    int a1[] = {14, 9, 12, 3, 78, 25, 36};

    HeapSort<int>  test1(a1, 7, std::less<int>());
    cout << endl;

    HeapSort<int, std::greater<int>> test2(a1, 7, std::greater<int>());
    cout << endl;

    HeapSort<int, CompareIntReverse> test3(a1, 7, CompareIntReverse());
    cout << endl;


    return 0;
}




