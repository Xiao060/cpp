#include <cstddef>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

class Computer {
public:
    // 创建一个 返回值为对象指针 的静态函数
    static Computer* getInstance() {
        if (_pInstance == nullptr) {
            _pInstance = new Computer();
        }

        return _pInstance;
    }

    void init(const char* brand, int price) {
        if (_brand) {
            delete [] _brand;
        }

        _brand = new char[strlen(brand) + 1]();
        strcpy(_brand, brand);
        _price = price;
    }

    void destroy() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    void print() {
        cout << "brand: " << _brand << endl
             << "price: " << _price << endl;
    }


private:
    // 从类中删除 拷贝构造函数 及 赋值运算符函数
    Computer(const Computer&)  = delete;
    Computer& operator=(const Computer&) = delete;
    // 无参构造函数采用默认的
    Computer() = default;

    // 析构函数 的访问权限一般与 构造构造函数 相同或更严格
    ~Computer() {
        if (_brand) {
            delete [] _brand;
            _brand = nullptr;
        }
    }

    char* _brand;
    int _price;
    // 创建一个指向对象的 静态指针
    static Computer* _pInstance;
};


Computer* Computer::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    Computer::getInstance()->init("HuaWei", 6200);
    Computer::getInstance()->print();

    Computer::getInstance()->init("Thinkbook", 5000);
    Computer::getInstance()->print();

    Computer::getInstance()->destroy();
    return 0;
}




