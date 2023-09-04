#include <iostream>
// using std::cin;
// using std::cout;
// using std::endl;

class Point {

public:
    Point(int ix = 0, int iy = 0) 
    : _ix(ix)
    , _iy(iy)
    , _iz(_iy)
    {}

private:
    const int _ix;
    int _iy;
    int &_iz;
};


int main(int argc, char* argv[]) {

    

    return 0;
}




