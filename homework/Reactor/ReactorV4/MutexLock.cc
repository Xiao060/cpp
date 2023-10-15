#include "MutexLock.hh"
#include <cstdio>
#include <pthread.h>


MutexLock::MutexLock(){
    // mutex 的 初始化, 无错则 返回 0
    int ret = pthread_mutex_init(&_mutex, nullptr);

    if (ret) {
        perror("pthread_mutex_init");
        return;
    }
}

MutexLock::~MutexLock(){
    int ret = pthread_mutex_destroy(&_mutex);

    if (ret) {
        perror("pthread_mutex_destroy");
        return;
    }
}


void MutexLock::lock() {
    int ret = pthread_mutex_lock(&_mutex);

    if (ret) {
        perror("pthread_mutex_lock");
        return;
    }
}

void MutexLock::trylock() {
    int ret = pthread_mutex_trylock(&_mutex);

    if (ret) {
        perror("pthread_mutex_trylock");
        return;
    }
}

void MutexLock::unlock() {
    int ret = pthread_mutex_unlock(&_mutex);

    if (ret) {
        perror("pthread_mutex_unlock");
        return;
    }
}


// 同步 的 wait() 需要用到 互斥锁
pthread_mutex_t* MutexLock::getMutexLockPtr() {
    return &_mutex;
}