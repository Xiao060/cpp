#include "Consumer.hh"
#include "Producer.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <algorithm>
#include <iostream>
#include <memory>
#include <pthread.h>

using std::unique_ptr;

int main(int argc, char* argv[]) {

    TaskQueue tq(10);

    unique_ptr<Thread> pro1(new Producer(tq));
    unique_ptr<Thread> pro2(new Producer(tq));
    unique_ptr<Thread> con1(new Consumer(tq));

    pro1->start();
    pro2->start();
    con1->start();

    pro1->stop();
    pro2->stop();
    con1->stop();

    return 0;
}