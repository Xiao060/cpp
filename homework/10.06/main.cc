#include "Consumer.hh"
#include "Producer.hh"
#include "TaskQueue.hh"
#include "Thread.hh"
#include <iostream>
#include <pthread.h>


int main(int argc, char* argv[]) {

    TaskQueue tq(10);

    Thread* pro1 = new Producer(tq);
    Thread* pro2 = new Producer(tq);
    Thread* con1 = new Consumer(tq);

    pro1->start();
    pro2->start();
    con1->start();

    pro1->stop();
    pro2->stop();
    con1->stop();

    return 0;
}