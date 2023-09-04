#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class Point {

public:
    Point(int ix = 0, int iy = 0, int iz = 0) 
    : _ix(ix)
    , _iy(iy)
    , _iz(iz)
    {}

private:
    const int _ix;
    const int _iy;
    int &_iz;
};


int main(int argc, char* argv[]) {

    

    return 0;
}




