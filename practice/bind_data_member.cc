 
#include <functional>
#include <iostream>
#include <ostream>

using std::bind;
using std::cout;
using std::endl;

class Example {
public:

    Example(int d)
    : data(d) {}

    int data = 100;
};


int main() {
    Example ex(12);
    auto f = bind(&Example::data, &ex);
    

    cout << f() << endl;

    return 0;
}
