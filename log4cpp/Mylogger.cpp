#include "Mylogger.hh"

using std::cout;
using namespace log4cpp;

// 类外初始化静态数据成员
Mylogger* Mylogger::_pInstance = nullptr;


Mylogger::Mylogger() 
: _mycat(Category::getRoot().getInstance("category")) {

    auto ptn1 = new PatternLayout();
    ptn1->setConversionPattern("%d %c [%p]: %m%n");

    auto ptn2 = new PatternLayout();
    ptn2->setConversionPattern("%d %c [%p]: %m%n");
    
    auto pos = new OstreamAppender("console", &cout);
    pos->setLayout(ptn1);

    auto pfile = new FileAppender("fileApp", "wd.log");
    pfile->setLayout(ptn2);

    _mycat.setPriority(Priority::DEBUG);
    _mycat.addAppender(pos);
    _mycat.addAppender(pfile);

    cout << "构造\n";
}

Mylogger::~Mylogger() {
    Category::shutdown();
    cout << "析构\n";
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

/*********************************/

void Mylogger::emerg(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.emerg(msg_full);
}

void Mylogger::fatal(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.fatal(msg_full);
}

void Mylogger::alert(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.alert(msg_full);
}

void Mylogger::crit(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.crit(msg_full);
}

void Mylogger::error(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.error(msg_full);
}

void Mylogger::warn(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.warn(msg_full);
}

void Mylogger::notice(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.notice(msg_full);
}

void Mylogger::info(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.info(msg_full);
}

void Mylogger::debug(const char* msg, const char* file, const char* func, const int& line) {
    char msg_full[1024] = {0};
    sprintf(msg_full, "(%s, %s, %d) %s", file, func, line, msg);
    _mycat.debug(msg_full);
}








