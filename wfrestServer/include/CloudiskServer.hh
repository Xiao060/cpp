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

    void start(unsigned short port);
    



private:
    void mysqlRegisterCallback(WFMySQLTask* mysqlTask);
    void mysqlLoginQueryCallback(WFMySQLTask* mysqlTask);
    
private:
    wfrest::HttpServer _httpServer;
    WFFacilities::WaitGroup _waitGroup;
};

#endif
