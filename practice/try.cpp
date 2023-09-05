#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void test();

int main(int argc, char* argv[]) {

    test();

    return 0;
}

void test() {
    double x, y;
    cin >> x >> y;

    try {
        if (y == 0)
            throw y;
        else 
            cout << (x/y) << endl;
    } catch(int e) {
        cout << "catch(int), e = " << e << endl;
    } catch(double d) {
        cout << "catch(double), y = " << y << endl;
    }

}



