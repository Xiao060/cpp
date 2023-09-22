#include <stdio.h>

class A {
public:
    void FuncA() {
        printf( "FuncA called\n" );
    }

    virtual void FuncB() {
        printf( "FuncB called\n" );
    }
};

class B 
: public A {
public:
    void FuncA() {
        A::FuncA();
        printf( "FuncAB called\n" );
    }
    
    virtual void FuncB() {
        printf( "FuncBB called\n" );
    }
};

int main( void ) {
    B b;
    A *pa;
    pa = &b;
    A *pa2 = new A;
    pa->FuncA();            // (3) 
    pa->FuncB();            // (4)
    pa2->FuncA();           // (5)
    pa2->FuncB();
    delete pa2;

    printf("\n");
    A *pa3 = new B;
    pa3->FuncA();           // (5)
    pa3->FuncB();
    delete pa3;

    return 0;
}
