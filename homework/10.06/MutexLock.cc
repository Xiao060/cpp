#include "MutexLock.hh"
#include <cstddef>
#include <cstdio>
#include <pthread.h>


MutexLock::MutexLock() {
    int ret = pthread_mutex_init(&_mutex, nullptr);

    if (ret) {
        perror("pthread_mutex_init");
    }
}

MutexLock::~MutexLock() {
    pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock() {
    pthread_mutex_lock(&_mutex);
}

void MutexLock::unlock() {
    pthread_mutex_unlock(&_mutex);
}

void MutexLock::trylock() {
    pthread_mutex_trylock(&_mutex);
}

pthread_mutex_t* MutexLock::getMutexLockPtr() {

}

