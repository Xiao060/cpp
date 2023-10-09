#include "MyTask.hh"
#include "Task.hh"
#include "ThreadPool.hh"
#include <memory>
#include <pthread.h>


using std::unique_ptr;


int main() {
    srand(time(nullptr));
    ThreadPool pool(4, 10);

    unique_ptr<Task> ptask(new MyTask());


    pool.start();

    int cnt = 10;
    while (cnt--) {
        pool.addTask(ptask.get());
    }


    pool.stop();

    return 0;
}