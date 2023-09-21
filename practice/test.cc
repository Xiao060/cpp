#include <iostream>

using std::cin;
using std::cout;
using std::endl;

template <class T, class K>
T add(T a, K b) {
    return a + b;
}

// 此处为重载函数模板, 不是偏特化
// 函数模板不支持偏特化
template <class T>
T add(T a, int b) {
    return a + b;
}

// add 后接 <> 为全特化
// add 后不接 <> 为 模板重载 ??????
template <>
double add<double, int>(double a, int b) {
    return a + b;
}

int main(int argc, char* argv[]) {

    cout << add(3, 4) << endl;
    cout << add(5, 5.9) << endl;
    
    return 0;
}




