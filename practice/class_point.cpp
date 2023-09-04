#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point {

public:
    Point(int x = 0, int y = 0) 
    : _ix(x), _iy(y) {
        cout << "Ponit()" << endl;
        _ix = x;
        _iy = y;
    }

    void print() {
        cout << "(" << _ix << ", " << _iy << ")" << endl;
    }

private:
    int _ix;
    int _iy;
};



int main(int argc, char* argv[]) {

    Point pt(4, 5);
    pt.print();

    return 0;
}




