#include <cstddef>
#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

// Singleton* Singleton<T>::pton = 

class Point {
public:
    Point(int x = 0, int y = 0) 
    : _ix(x)
    , _iy(y) {}

private:
    int _ix;
    int _iy;
};


class Computer {
public:
    Computer() 
    : _brand(nullptr)
    , _price(0) {}

    Computer(char* name, int price) 
    : _brand(new char[strlen(name) + 1]())
    , _price(price) {
        strcpy(_brand, _brand);
    }

    Computer(const Computer& rhs) 
    : _brand(new char[strlen(rhs._brand) + 1]())
    , _price(rhs._price) {
        strcpy(_brand, rhs._brand);
    }

    // 移动构造函数
    Computer(Computer&& rhs) 
    : _brand(rhs._brand)
    , _price(rhs._price) {
        rhs._brand = nullptr;
    }

    ~Computer() {
        if (_brand != nullptr) {
            delete [] _brand;
            _brand = nullptr;
        }
    }

    Computer& operator=(const Computer& rhs) {
        if (this != &rhs) {
            delete [] _brand;
            _brand = new char[strlen(rhs._brand) + 1]();
            strcpy(_brand, rhs._brand);
        }

        return *this;
    }

    // 移动赋值函数
    Computer& operator=(Computer&& rhs) {
        if (this != &rhs) {
            _brand = rhs._brand;
            rhs._brand = nullptr;
        }
        return *this;
    }

private:
    char* _brand;
    int _price;
};





template <class T = int>
class Singleton {
public:
    template <typename K, typename ...Args>
    Singleton& getInstance(K k, Args ...args) {
        if (_pInstance == nullptr) {
            new Singleton();
        }

        return _pInstance;
    }



    void destory() {

    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() 
    : _pInstance(new T()) {}

    ~Singleton() {
        delete _pInstance;
    }

    T* _pInstance;
};









Point pt(1, 2);
Point pt2(3, 4);

Computer com("Mac", 8888);

int main(void) {
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    assert(pc1 == pc2);
    
    Point* pt3 = Singleton<Point>::getInstance(1, 2);
    Point* pt4 = Singleton<Point>::getInstance(1, 2);
    assert(pt3 == pt4);
    
    return 0;
} 





