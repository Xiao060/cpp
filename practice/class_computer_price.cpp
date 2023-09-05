#include <iostream>
#include <cstring>
// using std::cin;
using std::cout;
using std::endl;


class Computer {

public:
    Computer(const char* brand, double price)
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
        _totalPrice += _price;
    }

    ~Computer() {
        delete [] _brand;
        cout << "~Computer()" << endl;
    }

    void print() {
        cout << "brand: " << _brand << endl;
        cout << "price: " << _price << endl;
        cout << "total price: " << _totalPrice << endl;
    }

    // 静态成员函数, 通过类名进行调用
    static void printTotalPrice() {
        cout << "Total price: " << _totalPrice << endl;
    }

private:
    char* _brand;
    double _price;
    static double _totalPrice;
};


// 类 的 静态变量 初始化
double Computer::_totalPrice = 0;

int main(int argc, char* argv[]) {

    Computer pc1("Thinkbook 16", 5000);
    // pc1.print();
    // 静态成员函数, 直接通过类名进行调用
    Computer::printTotalPrice();

    Computer pc2("redbook 16", 4999);
    // pc2.print();
    Computer::printTotalPrice();

    return 0;
}




