#include <iostream>
// using std::cin;
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

class Line {
public:
    Line(int x1, int y1, int x2, int y2)
    : _pt1(x1, y1)
    , _pt2(x2, y2)
    {
        cout << "Line(int, int, int, int)" << endl;
    }

    void print() {
        cout << "_pt1: ";
        _pt1.print();
         
        cout << "_pt2: ";
        _pt2.print();
    }

private:
    Point _pt1;
    Point _pt2;
};


int main(int argc, char* argv[]) {

    Line line(3, 6, 1, 8);
    
    line.print();
    return 0;
}




