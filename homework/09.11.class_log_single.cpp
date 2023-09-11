#include <cstddef>
#include <iostream>
#include <cstring>
// 设置 布局 的头文件
#include <log4cpp/PatternLayout.hh>
// 设置 目的地 的头文件
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
// 设置 源 的头文件
#include <log4cpp/Category.hh>
// 设置 优先级 的头文件
#include <log4cpp/Priority.hh>

using std::cout;
using namespace log4cpp;

class Mylogger {
public:
    static Mylogger* getInstance();
    void destory();

    void emerg(const char* msg, const char* file, const char* func, const int& line);
    void fatal(const char* msg, const char* file, const char* func, const int& line);
    void alert(const char* msg, const char* file, const char* func, const int& line);
    void crit(const char* msg, const char* file, const char* func, const int& line);
	void error(const char* msg, const char* file, const char* func, const int& line);
	void warn(const char* msg, const char* file, const char* func, const int& line);
    void notice(const char* msg, const char* file, const char* func, const int& line);
	void info(const char* msg, const char* file, const char* func, const int& line);
	void debug(const char* msg, const char* file, const char* func, const int& line);
 
    Mylogger(const Mylogger&) = delete;
    Mylogger& operator=(const Mylogger&) = delete;
	
private:
	Mylogger();
	~Mylogger();

    PatternLayout* _pat;
    OstreamAppender* _pos;
    Category& _cat;
    static Mylogger* _pInstance;
};

Mylogger::Mylogger() 
: _pat(new PatternLayout()) 
, _pos(new OstreamAppender("", &cout))
, _cat(Category::getRoot().getInstance("category")) {

    _pat->setConversionPattern("%d %c [%p]: %m%n");
    _pos->setLayout(_pat);
    _cat.setPriority(Priority::DEBUG);
    _cat.addAppender(_pos);
}

Mylogger::~Mylogger() {
    Category::shutdown();
}

Mylogger* Mylogger::getInstance() {
    if (_pInstance == nullptr) {
        _pInstance = new Mylogger();
    }
    return _pInstance;
}

void Mylogger::destory() {
    if (_pInstance) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

void Mylogger::emerg(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.emerg(msg_full);
}

void Mylogger::fatal(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.fatal(msg_full);
}

void Mylogger::alert(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.alert(msg_full);
}

void Mylogger::crit(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.crit(msg_full);
}

void Mylogger::error(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.error(msg_full);
}

void Mylogger::warn(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.warn(msg_full);
}

void Mylogger::notice(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.notice(msg_full);
}

void Mylogger::info(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.info(msg_full);
}

void Mylogger::debug(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _cat.debug(msg_full);
}



void test0() {
    //第一步，完成单例模式的写法
    Mylogger *log = Mylogger::getInstance();

    log->info("The log is info message", __FILE__, __FUNCTION__, __LINE__);
    log->error("The log is error message", __FILE__, __FUNCTION__, __LINE__);
    log->fatal("The log is fatal message", __FILE__, __FUNCTION__, __LINE__);
    log->crit("The log is crit message", __FILE__, __FUNCTION__, __LINE__);
}

Mylogger* Mylogger::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    test0();    

    return 0;
}




