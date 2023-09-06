#include <cstddef>
#include <iostream>
#include <assert.h>

// using std::cin;
using std::cout;
using std::endl;


class Singleton {
// 返回值为类指针的 静态成员函数
public:
    static Singleton* getInstance() {
        if (nullptr == _pInstance) {
            _pInstance = new Singleton();
        }

        return _pInstance;
    }

// 构造函数私有化
private:
    Singleton() {
        cout << "Singleton()" << endl;
    }

// 静态成员, 指向本类型的指针变量
private:
    static Singleton* _pInstance;
};


// 静态成员变量初始化, 不需要写 static
Singleton* Singleton::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    Singleton* p1 = Singleton::getInstance();
    Singleton* p2 = Singleton::getInstance();

    // assert 判断表达式是否为真, 为 假 则 终止执行
    assert(p1 == p2);
    assert(p1 == nullptr);

    return 0;
}




