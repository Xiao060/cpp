#include <iostream>

// using std::cin;
using std::cout;
using std::endl;

class NullPointCall {
public:
    static void test1();
    void test2();
    void test3(int test);
    void test4();

private:
    static int _static;
    int _test;
};

void NullPointCall::test1() {
    cout << "_static = " << _static << endl;
}

void NullPointCall::test2() {
    cout << "coding is very cool!" << endl;
}

void NullPointCall::test3(int test) {
    cout << "test = " << test << endl;
}

void NullPointCall::test4() {
    cout << "_test = " << _test << endl;
}


// 类 静态变量的初始化
int NullPointCall::_static = 8;

int main(int argc, char* argv[]) {
    NullPointCall* pNull = nullptr;
    pNull->test1();
    pNull->test2();
    pNull->test3(10);

    // 引发段错误
    pNull->test4();

    return 0;
}




