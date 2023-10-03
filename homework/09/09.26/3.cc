#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::endl;

using std::list;


int main(int argc, char* argv[]) {

    list<int> lst;

    auto it1 = lst.begin();
    auto it2 =  lst.end();

    if (it1 == it2) {
        cout << "=" << endl;
    }

    return 0;
}




