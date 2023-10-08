#include "Consumer.hh"
#include "iostream"
#include "unistd.h"

using std::cout;
using std::endl;


Consumer::Consumer(TaskQueue& taskQue) 
: _taskQue(taskQue) { }

Consumer::~Consumer() {

}


void Consumer::run() {
    while (1) {
        int rec = _taskQue.pop();

        cout << "receive: " << rec << endl;

        sleep(3);
    }
}
