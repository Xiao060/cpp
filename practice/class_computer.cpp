#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

class Computer {

public:
    Computer(const char* brand, double price)
    : _brand(new char[strlen(brand) + 1]())
    , _price(price)
    {
        strcpy(_brand, brand);
    }

    ~Computer() {
        delete [] _brand;
        cout << "~Computer()" << endl;
    }

    void print() {
        cout << "brand: " << _brand << endl;
        cout << "_price: " << _price << endl;
    }

private:
    char* _brand;
    double _price;
};


int main(int argc, char* argv[]) {

    Computer comp("Thinkbook 16", 5000);

    comp.print();

    return 0;
}




