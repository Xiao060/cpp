#include "ThreadPool.hh"
#include "MyTask.hh"
#include <functional>
#include <memory>


using std::bind;

int main() {
    ThreadPool pool(4, 10);
    pool.start();

    unique_ptr<MyTask> ptask(new MyTask);
    
    int cnt = 20;
    while (cnt--) {
        pool.addTask(bind(&MyTask::process, ptask.get()));
    }

    pool.stop();
    return 0;
}