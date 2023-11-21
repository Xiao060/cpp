#include <memory>

#include <iostream>
#include <ostream>
#include <string>

using std::string;
using std::cout;
using std::endl;




int main(int argc, char* argv[]) {

    std::auto_ptr<int>  t1(new int(10));

    std::auto_ptr<int> t2(t1);

    cout << t1.get() << endl;
    //cout << *t1.get() << endl;
    cout << t2.get() << endl;
    cout << *t2.get() << endl;

    return 0;
}




