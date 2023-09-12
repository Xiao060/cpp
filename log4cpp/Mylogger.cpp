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

void Mylogger::emerg(const char* msg) {
    _mycat.emerg(msg);
}

void Mylogger::fatal(const char* msg) {
    _mycat.fatal(msg);
}

void Mylogger::alert(const char* msg) {
    _mycat.alert(msg);
}

void Mylogger::crit(const char* msg) {
    _mycat.crit(msg);
}

void Mylogger::error(const char* msg) {
    _mycat.error(msg);
}

void Mylogger::warn(const char* msg) {
    _mycat.warn(msg);
}

void Mylogger::notice(const char* msg) {
    _mycat.notice(msg);
}

void Mylogger::info(const char* msg) {
    _mycat.info(msg);
}

void Mylogger::debug(const char* msg) {
    _mycat.debug(msg);
}








