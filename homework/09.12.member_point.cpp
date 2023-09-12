#include <iostream>

using std::cout;
using std::endl;

class Test {
public:
    int myadd(int x, int y) {
        return x + y;
    }
};

int main(int argc, char* argv[]) {

    typedef int (Test::*func)(int, int);
    func f_add = &Test::myadd; 

    // 形式 1, 对象变量为对象名, 使用 .*
    Test t1;
    int n = (t1.*f_add)(7, 8);
    cout << n << endl;

    // 形式 2, 对象变量为指针, 使用 ->*
    Test* t2 = new Test();
    n = (t2->*f_add)(4, 5);
    cout << n << endl;

    return 0;
}




