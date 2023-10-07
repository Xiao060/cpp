#include "Producer.hh"
#include "TaskQueue.hh"


Producer::Producer(TaskQueue& taskQue) 
: _taskQue(taskQue) { }

Producer::~Producer() {

}


void Producer::run() {

}
