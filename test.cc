#include <iostream>
#include <new>

using std::cin;
using std::cout;
using std::endl;
using std::string;

const int c = 10;

void test() {
    int n = 5;
    int* p = new int(10);
    string s = "Hello";
    static int b = 20;

    cout << &n << endl; 
    cout << &s << endl;
    cout << p << endl;
    cout << "c: " << &c << endl;
    cout << "b: " << &b << endl;

    [n, s](int* ptr){
        // cout << n << endl;
        cout << &n << endl;
        cout << &s << endl;
        cout << "c: " << &c << endl;
    } (p);
}

int main(int argc, char* argv[]) {

    test();
    

    return 0;
}




