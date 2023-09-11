//文件名: log4cpptest.cc
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/BasicLayout.hh>

using std::cout;

int main() {
    using namespace log4cpp;
    OstreamAppender *pOstreamApp = new OstreamAppender("console", &cout);
    pOstreamApp->setLayout(new BasicLayout());

    Category &logger = Category::getRoot().getInstance("logger");
    logger.setPriority(Priority::DEBUG);
    logger.setAppender(pOstreamApp);

    logger.debug("this is a debug message");
    logger.info("this is an info message");
    logger.notice("this is a notice message");
    logger.error("this is an error message");
    logger.crit("this is a critl message");
    logger.emerg("this is an emerg message");
    logger.alert("this is an alert message");
    logger.warn("this is a warn message");
    Category::shutdown();

    return 0;
}