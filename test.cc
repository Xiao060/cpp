#include <iostream>
#include <netinet/in.h>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
inline int SIZE2(T& array) {
    return sizeof(array) / sizeof(array[0]);
}


int main(int argc, char* argv[]) {
    

    int x[5];

    cout << SIZE2(x) << endl;

    return 0;
}




