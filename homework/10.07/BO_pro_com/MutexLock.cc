
#include "MutexLock.hh"    
#include <cstdio>
#include <pthread.h>

MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&_mutex, nullptr);

    if (ret) {
        perror("pthread_mutex_init");
        return ;
    }
}

MutexLock::~MutexLock() {
    int ret = pthread_mutex_destroy(&_mutex);

    if (ret) {
        perror("pthread_mutex_destory");
        return ;
    }
}

void MutexLock::lock() {
    int ret = pthread_mutex_lock(&_mutex);

    if (ret) {
        perror("pthread_mutex_lock");
        return ;
    }
}

void MutexLock::trylock() {
    int ret = pthread_mutex_trylock(&_mutex);

    if (ret) {
        perror("pthread_mutex_trylock");
        return ;
    }
}

void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&_mutex);

    if (ret) {
        perror("pthread_mutex_lock");
        return ;
    }
}


pthread_mutex_t* MutexLock::getMutexLockPtr() {
    return &_mutex;
}