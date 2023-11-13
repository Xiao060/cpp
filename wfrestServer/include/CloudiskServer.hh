#ifndef __CLOUDISKSERVER_HPP__
#define __CLOUDISKSERVER_HPP__

#include <wfrest/HttpServer.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFTaskFactory.h>

class CloudiskServer {

public:
    CloudiskServer(int n);
    
    void handler(int signum);

    void loadStaticResourceModule();

    void loadUserRegisterModule();

    void loadUserLoginModule();

    void loadUserInfoModule();

    void loadFileQueryModule();

    void start(unsigned short port);
    



private:
    void mysqlRegisterCallback(WFMySQLTask* mysqlTask);
    void mysqlLoginReadCallback(WFMySQLTask* mysqlTask);
    // 该函数完成的是写入操作, 回调函数非必要
    void mysqlLoginWriteCallback(WFMySQLTask* mysqlTask);
    void mysqlUserInfoCallback(WFMySQLTask* mysqlTask);


private:
    wfrest::HttpServer _httpServer;
    WFFacilities::WaitGroup _waitGroup;
};

#endif
