
void Thread::start() {
    // pthread_create 第三个参数 类型为 参数为 void*, 返回值为 void* 的函数指针
    // 若 threadFunc 作为 非静态 成员函数, 则 至少有一个参数 this 指针
    // 故 应该把 threadFunc 设为 静成员函数
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
