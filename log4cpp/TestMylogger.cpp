#include "Mylogger.hh"




void test0() {
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info(addprefix("The log is info message"));
    log->error(addprefix("The log is error message"));
    log->fatal(addprefix("The log is fatal message"));
    log->crit(addprefix("The log is crit message"));
}

int main(int argc, char* argv[]) {

    test0();    

    return 0;
}