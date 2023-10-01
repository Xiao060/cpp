#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


class Test {
   
public:
    Test(string s) 
    : _s(s) {}

    char& operator[](size_t i) {
        return _s[i];
    }

    const char& operator[](size_t i) const {
        return _s[i];
    }

   
private:

    string _s;
    static const int _x = 12;
    const int _y = 13;
   
};


void print(const Test& t) {
    cout << t[0] << endl;
}


int main(int argc, char* argv[]) {

    Test x("Hello");

    cout << x[0] << endl;

    x[0] = 'G';
    
    cout << x[0] << endl;

    return 0;
}




