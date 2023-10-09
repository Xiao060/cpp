#ifndef __MYTASK_HPP__
#define __MYTASK_HPP__

#include "Task.hh"
#include <cstdlib>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;


class MyTask 
: public Task {

public:
    MyTask() = default;
    ~MyTask() = default;
    
    void process() override {
        srand(time(nullptr));

        int num = rand() % 1000;
        cout << "MyTask num = " << num << endl;
    }
};

#endif
