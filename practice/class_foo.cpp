#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Foo {

public:
    Foo(int a) 
    : _iy(a)
    , _ix(_iy)  // 在类中先声明 _ix, 后声明 _iy; 初始化顺序即为声明顺序, 此时 _iy 还未被初始化
    {
        cout << "Foo(int)" << endl;
    }

private:
    int _ix;
    int _iy;
};

int main(int argc, char* argv[]) {

    

    return 0;
}




