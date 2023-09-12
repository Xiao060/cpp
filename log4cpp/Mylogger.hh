#include <iostream>
#include <string>
#include <cstring>
// 设置 布局 的头文件
#include <log4cpp/PatternLayout.hh>
// 设置 目的地 的头文件
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
// 设置 源 的头文件
#include <log4cpp/Category.hh>
// 设置 优先级 的头文件
#include <log4cpp/Priority.hh>

using std::cout;
using std::string;
using std::to_string;
using namespace log4cpp;

#define addprefix(msg) string("[").append(__FILE__)         \
        .append(":").append(__FUNCTION__)                   \
        .append(":").append(to_string(__LINE__))            \
        .append("] ").append(msg).c_str()


class Mylogger {
public:
    static Mylogger* getInstance();
    static void destory();

    void emerg(const char* msg);
    void fatal(const char* msg);
    void alert(const char* msg);
    void crit(const char* msg);
	void error(const char* msg);
	void warn(const char* msg);
    void notice(const char* msg);
	void info(const char* msg);
	void debug(const char* msg);
 
    Mylogger(const Mylogger&) = delete;
    Mylogger& operator=(const Mylogger&) = delete;
	
private:
	Mylogger();
	~Mylogger();

    Category& _mycat;
    static Mylogger* _pInstance;
};

