#include "String.hh"
#include <iostream>

using std::cout;
using std::endl;

int main() {

    String s1(String("Hello"));
    cout << s1 << endl;

    String s4 = String("Fine");
    cout << s4 << endl;

    return 0;
}