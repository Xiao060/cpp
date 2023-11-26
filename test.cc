#include <iostream>
#include <new>

using std::cin;
using std::cout;
using std::endl;
using std::string;


void test() {
    int n = 5;
    int* p = new int(10);
    string s = "Hello";

    cout << &n << endl; 
    cout << &s << endl;
    cout << p << endl;

    [n, s](int* ptr){
        // cout << n << endl;
        cout << &n << endl;
        cout << &s << endl;
    } (p);
}

int main(int argc, char* argv[]) {

    test();
    

    return 0;
}




