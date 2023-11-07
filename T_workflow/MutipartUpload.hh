#ifndef __MUTIPARTUPLOAD_HPP__
#define __MUTIPARTUPLOAD_HPP__

// 分片上传

// 用于阻塞主线程
#include <workflow/WFFacilities.h>
// 用于创建 http 服务端
#include <workflow/WFHttpServer.h>
#include <workflow/WFTaskFactory.h>

class MultipartUpload {

public:
    MultipartUpload(int n);
    void start(unsigned short port);
    
private:
    void process(WFHttpTask* httpTask);  
    void init(WFHttpTask* httpTask);
    void uppart(WFHttpTask* httpTask);
    void complete(WFHttpTask* httpTask);
    void redisCallback(WFRedisTask* redisTask);
    
private:
    WFFacilities::WaitGroup waitGroup; 
    WFHttpServer httpServer;
};



#endif
