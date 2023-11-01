#include <iostream>
#include <workflow/WFFacilities.h>
#include <csignal>

using std::cout;
using std::endl;


//wait_group的参数用来表示有多少个任务还没完成
static WFFacilities::WaitGroup wait_group(1);

void sig_handler(int signo){

    cout << "SIGINT" << endl;

    //done方法表示完成了一个任务
    wait_group.done();
}

int main(){

    //wait方法当存在至少一个任务未完成时,线程阻塞。
    signal(SIGINT, sig_handler);
    wait_group.wait();

    return 0;
}