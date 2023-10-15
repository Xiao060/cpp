#include <cstdio>
#include <iostream>
#include <utility>

using std::cin;
using std::cout;
using std::endl;




int main(int argc, char* argv[]) {

    int x = 5;
    int y;

    y = std::move(x);
    
    printf("&x = %p\n", &x);
    printf("&y = %p\n", &y);


    y += 1;
    printf("&x = %p\n", &x);
    printf("&y = %p\n", &y);

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;


    return 0;
}




