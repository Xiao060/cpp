#include "MutipartUpload.hh"
#include "MutipartUpload.hh"

#include <cstddef>
#include <cstdio>
#include <ctime>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>

#include <workflow/HttpMessage.h>
// 用于获取错误信息
#include <workflow/RedisMessage.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <nlohmann/json.hpp>
#include <workflow/Workflow.h>
#include <workflow/http_parser.h>




using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector;
using std::bind;
using std::placeholders::_1;

MultipartUpload::MultipartUpload(int n) 
: waitGroup(1)
, httpServer(bind(&MultipartUpload::process, this, _1)) { }


void MultipartUpload::start(unsigned short port) {
    if (httpServer.start(port) == 0) {
        waitGroup.wait();
        httpServer.stop();
    }
}


void MultipartUpload::process(WFHttpTask* httpTask) {
    // 1. 检测连接状态
    int state = httpTask->get_state();
    int error = httpTask->get_error();
    if (state != WFT_STATE_TOREPLY) {
        cout << WFGlobal::get_error_string(state, error);
    }

    // 2. 获取 请求方法 与 uri 
    protocol::HttpRequest* req = httpTask->get_req();
    string method = req->get_method();
    string uri = req->get_request_uri();
    uri = uri.substr(0, uri.find("?"));


    // 3. 根据 请求方法 与 uri 进行不同的处理 
    if (method == "POST" && uri == "/file/mupload/init") {
        // POST http://192.168.30.128:8888/file/mupload/init?username=liubei
        // 阶段一 主要完成的功能
        // 1. 解析请求, 得到 username (uri获取), filename/filesize/filehash (后3项从报文体中获取) 
        // 2. 计算分片信息, 得到 chunksize / chunkcnt
        // 3. 生成文件的唯一标识, unloadid, 即 username + 年月日时分秒
        // 4. 生成响应报文, 以 JSON 格式发送
        // 5. 将 uploadid : {filename, filehash, filesize, chunksize, chunkcnt} 以 HASH 类型保存到 Redis中
        // 故 init 函数 需要访问 httpTask 的 req 与 resp, 为了方便此处直接把 httpTask 作为参数传递进去
        init(httpTask);
    } else if (method == "POST" && uri == "/file/mupload/uppart") {
        // POST 192.168.30.128:8888/file/mupload/uppart?uploadid=liubeixxxxx&chunkidx=0
        // 阶段二 功能
        // 1. 解析请求, 获取 uploadid, chunkidx 以及报文体中的 文件内容
        // 2. 以 uploadid 建立目录, 将 文件内容 写入磁盘文件, 磁盘文件名称 即为 chunkidx 
        // 3. 生成响应信息
        // 4. 将 已写入磁盘文件的 分片信息 以 uploadid : {chunidx_x : 1} 的格式加入 redis
        // 此处 可以先完成 第 1 步, 然后将值 作为参数传入 uppart() 函数, 不过 此处为了整洁??直接传入 httpTask, 由 uppart 自己去获取数据
        uppart(httpTask);
    } else if (method == "GET" && uri == "/file/mupload/complete") {
        // GET 192.168.30.128:8888/file/mupload/complete?uploadid=liubeixxxx
        // 阶段三 功能
        // 1. 解析请求, 得到 uploadid
        // 2. 进行验证, 从 redis 中取得 uploadid 的相关信息, 得到 chunkcnt, hash 与 分片数量 
        //    比较 分片数量 与 chunkcnt 是否相等, 相等则合并文件, 再计算 hash值 与 取出的 hash 比较
        complete(httpTask);
    }
    

}


void MultipartUpload::init(WFHttpTask* httpTask) {
    // POST http://192.168.30.128:8888/file/mupload/init?username=liubei

    // 1. 获取 username 与 filename/filesize/filehash
    string uri = httpTask->get_req()->get_request_uri();
    string username = uri.substr(uri.find("=")+1);
    cout << "\e[93m*****************************************************\e[39m" << endl;
    cout << "\e[93musername: \e[39m" << username << endl;

    const void* body;
    size_t size;
    httpTask->get_req()->get_parsed_body(&body, &size);
    using Json = nlohmann::json;
    // json 反序列化
    Json jsonBody = Json::parse((const char*) body);
    // NOTE: 注意: 此处 json 中 filesize 即为数字, 取出来便是数字, 不需要在进行类型转换
    string filename = jsonBody["filename"];
    size_t filesize = jsonBody["filesize"];
    string filehash = jsonBody["filehash"];
    cout << "\e[93mfilename: \e[39m" << filename << endl;
    cout << "\e[93mfilesize: \e[39m" << filesize << endl;
    cout << "\e[93mfilehash: \e[39m" << filehash << endl;

    // 2. 获取/计算 分片信息
    size_t chunksize = 100 * 1024 * 1024;
    size_t chunkcnt = filesize / chunksize + (filesize % chunksize > 0 ? 1 : 0);

    // 3. 生成上传文件的唯一标识
    time_t nowSecond;
    time(&nowSecond);
    struct tm* now = localtime(&nowSecond);
    char nowStr[15] = {0};
    sprintf(nowStr, "%04d%02d%02d%02d%02d%02d",
                        now->tm_year + 1900, 
                        now->tm_mon, 
                        now->tm_mday, 
                        now->tm_hour, 
                        now->tm_min, 
                        now->tm_sec);
    string uploadid = username + nowStr;

    cout << "\e[93muploadid: \e[39m" << uploadid << endl;
    cout << "\e[93m*****************************************************\e[39m" << endl;

    // 4. 生成响应报文, 以 JSON 方式发送
    jsonBody["chunksize"] = chunksize;
    jsonBody["chunkcnt"] = chunkcnt;
    jsonBody["uploadid"] = uploadid;
    httpTask->get_resp()->append_output_body(jsonBody.dump(2));

    // 5. 将 uploadid : {filename, filesize, filehash, chunksize, chunkcnt} 以 hash 类型保存到 redis 中
    WFRedisTask* redisTask = WFTaskFactory::create_redis_task("redis://localhost", 1, nullptr);
    string command = "hset";
    vector<string> params = { uploadid,
                            "filename", filename,
                            "filesize", to_string(filesize),
                            "filehash", filehash,
                            "chunksize", to_string(chunksize),
                            "chunkcnt", to_string(chunkcnt) };
    redisTask->get_req()->set_request(command, params);

    series_of(httpTask)->push_back(redisTask);

}


void MultipartUpload::uppart(WFHttpTask* httpTask) {

    // POST 192.168.30.128:8888/file/mupload/uppart?uploadid=liubeixxxxx&chunkidx=0
    // 1. 获取 uploadid, chunkidx 及 报文体中的 文件内容
    protocol::HttpRequest* req = httpTask->get_req();
    string uri = req->get_request_uri();
    string uploadidPair = uri.substr(0, uri.find("&"));
    string chunkidxPair = uri.substr(uri.find("&")+1);
    string uploadid = uploadidPair.substr(uploadidPair.find("=") + 1);
    string chunkidx = chunkidxPair.substr(chunkidxPair.find("=") + 1);

    const void* body;
    size_t size;
    req->get_parsed_body(&body, &size);

    cout << "\e[93m*****************************************************\e[39m" << endl;
    cout << "\e[93muploadid: \e[39m" << uploadid << endl;
    cout << "\e[93mchunkidx: \e[39m" << chunkidx << endl;
    cout << "\e[93mbody: \e[39m\n" << (char*) body << endl;
    cout << "\e[93m*****************************************************\e[39m" << endl;

    // 2. 以 uploadid 为名建立 目录, 将 文件内容 写入该目录下的磁盘文件, 文件名即为 chunkidx
    // 若 建目录/打开文件失败/..., 则 整个 uppart() 函数失败, 所以 需要生成失败的响应报文
    protocol::HttpResponse* resp = httpTask->get_resp();
    // 创建目录前 先通过 acess 函数判断目录是否存在, 存在则返回值为 0, 不存在返回 -1
    // 此处 若 目录已存在, 则返回值为-1 并 设置 error
    // 所以此处 不建议
    if (access(uploadid.c_str(), F_OK) == -1) {
        int ret = mkdir(uploadid.c_str(), 0755);
        resp->set_status_code("500");
        resp->set_reason_phrase("Internal Server Error");
        resp->append_output_body("Uppart Failed!");
        perror("open");
        return;
    }

    string filename = uploadid + "/" + chunkidx;
    int fd = open(filename.c_str(), O_CREAT | O_RDWR);
    if (fd == -1) {
        resp->set_status_code("500");
        resp->set_reason_phrase("Internal Server Error");
        resp->append_output_body("Uppart Failed!");
        perror("open");
        return;
    }

    write(fd, (const char*) body, size);
    close(fd);

    // 3. 生成 响应报文
    resp->append_output_body("Uppart Success!");

    // 4. 将已经写入磁盘文件的 分片信息以 uploadid : {chunkidx_x : 1} 的格式加入到 redis
    WFRedisTask* redisTask = WFTaskFactory::create_redis_task("redis://localhost", 1, nullptr);
    string command = "hset";
    vector<string> params = {uploadid,
                            "chunkidx_" + chunkidx, "1"};
    redisTask->get_req()->set_request(command, params);
    series_of(httpTask)->push_back(redisTask);

}


void MultipartUpload::complete(WFHttpTask* httpTask) {

    // 1. 解析请求, 获取 uploadid
    string uri = httpTask->get_req()->get_request_uri();
    string uploadid = uri.substr(uri.find("=") + 1);

    // 2. 从 redis 中取出 uploadid 对应的 hash表, 并进行 验证, 根据验证结果设置 http 的响应报文
    // 故 redisCallback 需要共享 httpTask 的响应报文
    WFRedisTask* redisTask = WFTaskFactory::create_redis_task("redis://localhost",
                                                            1, 
                                                            bind(&MultipartUpload::redisCallback, this, _1));
    string command = "hgetall";
    vector<string> params = {uploadid};
    redisTask->get_req()->set_request(command, params);
    // 设置共享数据
    redisTask->user_data = httpTask->get_resp();
    series_of(httpTask)->push_back(redisTask);

}


void MultipartUpload::redisCallback(WFRedisTask* redisTask) {

    // 获取 httpTask 的响应报文
    protocol::HttpResponse* httpResp = (protocol::HttpResponse*) redisTask->user_data;

    // 1. 状态检测
    int state = redisTask->get_state();
    int error = redisTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        httpResp->set_status_code("500");
        httpResp->set_reason_phrase("Internal Server Error");
        httpResp->append_output_body("Complete Failed!");
        cout << WFGlobal::get_error_string(state, error);
        return;
    }

    // 2. 获取 响应
    protocol::RedisResponse* redisResp = redisTask->get_resp();
    protocol::RedisValue value;
    redisResp->get_result(value);

    if (value.is_array()) {
        string filehash;
        size_t chunkcnt = 0;
        for (int i = 0; i < value.arr_size(); i+=2) {
            if (value.arr_at(i).string_value() == "chunkcnt") {
                chunkcnt = atoi(value.arr_at(i+1).string_value().c_str());
            }

            if (value.arr_at(i).string_value() == "filehash") {
                filehash = value.arr_at(i+1).string_value();
            }
        }

        size_t loadNum = (value.arr_size() - 10) / 2;

        cout << "\e[93m*****************************************************\e[39m" << endl;
        cout << "\e[93mchunkcnt: \e[39m" << chunkcnt << endl;
        cout << "\e[93mloadNum: \e[39m" << loadNum << endl;
        cout << "\e[93m*****************************************************\e[39m" << endl;

        if (chunkcnt == loadNum) {
            // 合并文件
            // 计算 hash
            // 比较 hash
            // 删除临时文件夹

            httpResp->append_output_body("Complete Success!");
            return;
        }
    }

    // 走到此处
    // 1. redis 返回值不是数组
    // 2. chunkcnt != loadNum
    // 3. filehash != hash
    httpResp->set_status_code("500");
    httpResp->set_reason_phrase("Internal Server Error");
    httpResp->append_output_body("Complete Failed!");

}