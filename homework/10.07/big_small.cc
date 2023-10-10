#include <cstdio>
#include <iostream>


int main(int argc, char* argv[]) {

    int x = 0x12345678;

    char* y = reinterpret_cast<char*>(&x);

    printf("%x\n", *y);
    
    return 0;
}




