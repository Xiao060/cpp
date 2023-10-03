#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

template <typename T>
void display(T t) {

    auto it = t.begin();

    for ( ; it != t.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    int a[] = {3, 6, 8, 5, 1, 0};

    vector<int> vec(a, a+6);
    display(vec);

    return 0;
}




