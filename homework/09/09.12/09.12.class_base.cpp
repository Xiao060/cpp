#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    Base(int num = 0);

    friend int operator+(const Base& lhs, const Base& rhs);

private:
    int _num;
};

Base::Base(int num) 
: _num(num) {}

int operator+(const Base& lhs, const Base& rhs) {
    return rhs._num - lhs._num;
}


int main(int argc, char* argv[]) {

    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);

    cout << (x+y == j-i) << endl;

    return 0;
}




