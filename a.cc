#include <memory>

#include <iostream>
#include <ostream>
#include <string>

using std::string;
using std::cout;
using std::endl;


template<class X>
X add(X a, X b);


int main(int argc, char* argv[]) {

    // std::auto_ptr<int>  t1(new int(10));

    // std::auto_ptr<int> t2(t1);

    // cout << t1.get() << endl;
    // //cout << *t1.get() << endl;
    // cout << t2.get() << endl;
    // cout << *t2.get() << endl;

    // int* p = nullptr;
    // delete p;
    // cout << *p << endl;

    cout << add(1, 5) << endl;
    cout << add(4.3, 5.2) << endl;


    return 0;
}


template<class X>
X add(X a, X b) {
    return a + b;
}




