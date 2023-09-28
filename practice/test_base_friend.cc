// 友元不能继承
// 即使是用基类指针指向的派生类 也不行


#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class BaseB;

class BaseA {
public:
    friend class BaseB;

    int getA() {
        return a;
    }

private:
    int a = 1;
};


class BaseB {
public:
    int getB() {
        return b;
    }

private:
    int b = 2;
};


class C 
: public BaseA {
public:
    int getC() {
        return c;
    }

private:
    int c = 3;
};

class D 
: public BaseB {
public:

    void test() {
        C tc;
        BaseA& ta = tc;
        ta.getA();

    }
    


    int getD() {
        return d;
    }

private:
    int d = 3;
};



int main(int argc, char* argv[]) {

    BaseB b;

    cout << b.getB() << endl;
    

    return 0;
}




