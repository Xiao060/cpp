#include <iostream>
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
using namespace log4cpp;


class Mylogger {
public:
    static Mylogger* getInstance();
    static void destory();

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

    Category& _mycat;
    static Mylogger* _pInstance;
};

