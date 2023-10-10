#ifndef __MYTASK_HPP__
#define __MYTASK_HPP__

#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;


class MyTask {

public:
    
    void process() {
        srand(clock());

        int num = rand() % 1000;
        cout << "num = " << num << endl;
    }
};

#endif
