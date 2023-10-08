#include "Consumer.hh"
#include "Producer.hh"
#include "TaskQueue.hh"
#include <iostream>
#include <pthread.h>

void* proThreadFunc(void * args);
void* conThreadFunc(void * args);

int main(int argc, char* argv[]) {

    TaskQueue tq(10);

    Producer pro(tq);
    Consumer con(tq);

    pthread_t pro1;    
    pthread_t con1, con2;    

    pthread_create(&pro1, nullptr, proThreadFunc, &pro);

    pthread_create(&con1, nullptr, conThreadFunc, &con);
    pthread_create(&con2, nullptr, conThreadFunc, &con);

    pthread_join(pro1, nullptr);
    pthread_join(con2, nullptr);
    pthread_join(con2, nullptr);

    return 0;
}


void* proThreadFunc(void * args) {
    Producer* ppro = (Producer*) args;

    ppro->run();

    return nullptr;
}


void* conThreadFunc(void * args) {
    Consumer* pcon = (Consumer*) args;

    pcon->run();

    return nullptr;
}