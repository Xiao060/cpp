#include "Producer.hh"
#include "TaskQueue.hh"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

Producer::Producer(TaskQueue& taskQue) 
: _taskQue(taskQue) { }

Producer::~Producer() {

}


void Producer::run() {
    srand(time(nullptr));

    while (1) {
        int send = rand() % 1000;
        _taskQue.push(send);
        cout << "send: " << send << endl;

        sleep(1);
    }
}
