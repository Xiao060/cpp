 
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

int add(int x, int y) {
    return x + y;
}

int main() {
    Example ex(12);
    auto f = bind(&Example::data, &ex);
    
    auto f1 = bind(&add, 10, 20);

    std::function<int()> f2 = bind(&add, 10, 20);

    cout << f() << endl;

    return 0;
}
