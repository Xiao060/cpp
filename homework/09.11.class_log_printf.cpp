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

    friend void LogEmerg(const char* msg, const char* file, const char* func, const int& line);
    friend void LogFatal(const char* msg, const char* file, const char* func, const int& line);
    friend void LogAlert(const char* msg, const char* file, const char* func, const int& line);
    friend void LogCrit(const char* msg, const char* file, const char* func, const int& line);
	friend void LogError(const char* msg, const char* file, const char* func, const int& line);
	friend void LogWarn(const char* msg, const char* file, const char* func, const int& line);
    friend void LogNotice(const char* msg, const char* file, const char* func, const int& line);
	friend void LogInfo(const char* msg, const char* file, const char* func, const int& line);
	friend void LogDebug(const char* msg, const char* file, const char* func, const int& line);
 
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

void LogEmerg(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.emerg(msg_full);
}

void LogFatal(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.fatal(msg_full);
}

void LogAlert(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.alert(msg_full);
}

void LogCrit(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.crit(msg_full);
}

void LogError(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.error(msg_full);
}

void LogWarn(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.warn(msg_full);
}

void LogNotice(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.notice(msg_full);
}

void LogInfo(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.info(msg_full);
}

void LogDebug(const char* msg, const char* file, const char* func, const int& line) {
    Mylogger *log = Mylogger::getInstance();

    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    log->_cat.debug(msg_full);
}

void test1() {
    //第二步，像使用printf一样
    //只要求能输出纯字符串信息即可，不需要做到格式化输出
    LogInfo("The log is info message", __FILE__, __FUNCTION__, __LINE__);
    LogError("The log is error message", __FILE__, __FUNCTION__, __LINE__);
    LogWarn("The log is warn message", __FILE__, __FUNCTION__, __LINE__);
    LogDebug("The log is debug message", __FILE__, __FUNCTION__, __LINE__);
}


Mylogger* Mylogger::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    test1();    

    return 0;
}




