#include "Condition.hh"
#include <cstdio>
#include <pthread.h>

Condition::Condition(MutexLock& mutex) 
: _mutex(mutex) {
    int ret = pthread_cond_init(&_cond, nullptr);

    if (ret) {
        perror("pthread_cond_init");
    }
}

Condition::~Condition() {
    pthread_cond_destroy(&_cond);
}


void Condition::wait() {
    int ret = pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());

    if (ret) {
        perror("pthread_cond_wait");
    }
}

void Condition::notify() {
    int ret = pthread_cond_signal(&_cond);

    if (ret) {
        perror("pthread_cond_signal");
    }
}

void Condition::notifyAll() {
    int ret = pthread_cond_broadcast(&_cond);

    if (ret) {
        perror("pthread_cond_broadcast");
    }
}
