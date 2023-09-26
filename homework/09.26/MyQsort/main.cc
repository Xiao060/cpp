#include <functional>
#include <iostream>
#include "MyQsort.hh"

using std::less;

int main(int argc, char* argv[]) {

    int p[] = {1, 12, 6, 11, 18, 10, 2, 5, 13, 7};

    std::less<int> tmp;

    MyQsort<int> t(p, 10, tmp);

    return 0;
}




