#include <iostream>
// 设置布局的头文件
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>
// 设置目的地的头文件
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
// 设置布局的头文件
#include <log4cpp/Category.hh>
// 设置优先级的头文件
#include <log4cpp/Priority.hh>

using std::cout;
using namespace log4cpp;

int log();

int main(int argc, char* argv[]) {

    log();

    return 0;
}

int log() {
    // 1.创建布局对象 并 设置布局
    // 默认的格式
    PatternLayout* pat1 = new PatternLayout();
    pat1->setConversionPattern("%d %c [%p]: %m%n");

    PatternLayout* pat2 = new PatternLayout();
    pat2->setConversionPattern("%d %c [%p]: %m%n");

    PatternLayout* pat3 = new PatternLayout();
    pat3->setConversionPattern("%d %c [%p]: %m%n");

    // 2.设置目的地对象 并 绑定布局
    OstreamAppender* pos = new OstreamAppender("terminal", &cout);
    pos->setLayout(pat1);
    
    FileAppender* pfile = new FileAppender("file", "log_file");
    pfile->setLayout(pat2);
    
    auto proll = new RollingFileAppender("rolling", "log", 10*1024, 4);
    proll->setLayout(pat3);

    // 3.设置源对象 并 设置优先级, 绑定目的地
    Category& cat = Category::getRoot().getInstance("category");
    cat.setPriority(Priority::DEBUG);
    cat.addAppender(pos);
    cat.addAppender(pfile);
    cat.addAppender(proll);

    // 4.记录日志
    for (int i=0; i < 100; ++i) {
        cat.debug("This is debug!");
        cat.info("This is info!");
        cat.notice("This is notice!");
        cat.warn("This is warn!");
        cat.error("This is error!");
        cat.crit("This is crit!");
        cat.alert("This is alert!");
    }

    // 日志系统退出
    Category::shutdown();

    return 0;
}

