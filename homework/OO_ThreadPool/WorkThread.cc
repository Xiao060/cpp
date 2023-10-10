#include "WorkThread.hh"


WorkThread::WorkThread(ThreadPool& pool) 
: _pool(pool) {

}

void WorkThread::run() {
    _pool.doTask();
}