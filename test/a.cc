#include <iostream>
#include <functional>

using std::function;
using std::bind;

typedef void(*type)();

void foo() {
    std::cout << "Hello, world!" << std::endl;
}

int main() {
    function<void()> func = bind(&foo);

    if (auto ptr = *(func.target<type>())) {
        std::cout << "Function address: " << ptr << std::endl;
        ptr();
    } else {
        std::cout << "Function not found!" << std::endl;
    }

    return 0;
}