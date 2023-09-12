#include "Mylogger.hh"




void test0() {
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message", __FILE__, __FUNCTION__, __LINE__);
    log->error("The log is error message", __FILE__, __FUNCTION__, __LINE__);
    log->fatal("The log is fatal message", __FILE__, __FUNCTION__, __LINE__);
    log->crit("The log is crit message", __FILE__, __FUNCTION__, __LINE__);
}

int main(int argc, char* argv[]) {

    test0();    

    return 0;
}