#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


int partition(int left, int right);
int print(int* p, int sz);
void quick(int left, int right);

int _vec[] = {6, 23, 12, 1, 8, 17, 2, 15, 3, 7};


// 1 2 3 5 6 7 8 12 17 23

int main(int argc, char* argv[]) {

    print(_vec, 10);

    // partition(0, 9);
    quick(0, 9);

    print(_vec, 10);

    return 0;
}


int print(int* p, int sz) {
    for (int i=0; i < sz; ++i) {
        cout << _vec[i] << " ";
    }
    cout << endl;

    return 0;
}


void quick(int left, int right) {

    if (left >= right) {
        return ;
    }

    int index = partition(left, right);

    quick(left, index-1);
    quick(index+1, right);
}




int partition(int left, int right) {

    int basic = _vec[right];

    int lt = left;
    int rt = right;
    
    while (lt <= rt) {
        while (lt < rt && _vec[lt] < basic) {
            ++lt;
        }

        if (lt == rt) {
            _vec[lt] = basic;
            break;
        } else {
            _vec[rt--] = _vec[lt];
        }

        while (lt < rt && basic < _vec[rt]) {
            --rt;
        }

        if (lt == rt) {
            _vec[lt] = basic;
            break;
        } else {
            _vec[lt++] = _vec[rt];
        }
    }

    return lt;
}
