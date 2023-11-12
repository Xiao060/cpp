#include <csignal>
#include <iostream>
#include <map>
#include <string>


// 用于 阻塞主进程
#include <map>
#include <vector>
#include <wfrest/HttpContent.h>
#include <wfrest/HttpDef.h>
// #include <wfrest/HttpFile.h>
#include <wfrest/Json.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFFacilities.h>
#include <wfrest/HttpMsg.h>
#include <wfrest/HttpServer.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>



using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;




WFFacilities::WaitGroup waitGroup(1);

void handler(int signum) {
    waitGroup.done();
}

void getQueryHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {

    cout << "\e[93m************************************\e[39m" << endl;

    // 1. 打印查询词
    // 1.1 通过 key 的方式来访问对应的 value
    // cout << req->query("username") << endl;
    // 1.2 得到所有 查询词构成的 map, 遍历 map
    map<string, string> queryList = req->query_list();
    for (auto& elem : queryList) {
        cout << "\e[93m" << elem.first << ":\e[39m " << elem.second << endl;
    }

    // 2. 创建 响应报文
    // 2.1 类型为 str
    resp->String("/query");
}


void postRawHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {

    cout << "\e[93m************************************\e[39m" << endl;

    // 1. 打印报文
    // 1.1 纯文本, raw, 即 text/plain
    cout << "\e[93mbody:\e[39m\n" << req->body() << endl;

    // 2. 创建 响应报文
    resp->String("/raw");
}


void getFormdataHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {
    resp->File("File.html");
}


void postFormdataHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {

    if (req->content_type() == wfrest::MULTIPART_FORM_DATA) {

        wfrest::Form from = req->form();
        for (auto& elem : from) {
            cout << elem.first << "\e[93m:\e[39m " 
                << elem.second.first << "\e[93m:\e[39m \n" 
                <<  elem.second.second << endl;

            resp->Save(elem.second.first, elem.second.second);
        }

        resp->String("/formdata");
    }
}


void postUrlencodedHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {
    
    map<string, string> formKv = req->form_kv();
    for (auto& elem : formKv) {
        cout << elem.first << ": " << elem.second << endl;
    }

    resp->String("/urlencoded");
}


void postJsonHandler(const wfrest::HttpReq* req, wfrest::HttpResp* resp) {

    wfrest::Json json = req->json();
    cout << "username: " << json["username"] << endl;
    cout << "age: " << json["age"] << endl;
    cout << json.dump() << endl;

    resp->String("/json");
}


int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    wfrest::HttpServer httpServer;

    // 1. 获取 查询词
    httpServer.GET("/query", getQueryHandler);

    // 2. 获取 纯文本 请求报文
    httpServer.POST("/raw", postRawHandler);

    // 3. 获取 文件 请求报文, 即 formdata
    httpServer.GET("/formdata", getFormdataHandler);
    httpServer.POST("/formdata", postFormdataHandler);

    // 4. 获取 urlencoded 请求报文, 即 x-www-form-urlencoded
    httpServer.POST("/urlencoded", postUrlencodedHandler);

    // 5. 获取 JSON 请求报文
    // NOTE:此处请求报文中 首部字段 Content-Type 为 application/json
    // 且 报文体格式为 json格式
    httpServer.POST("/json", postJsonHandler);

    // MySQL 使用方法 1
    // NOTE: wfrest v0.9.3 存在问题, 需要修改 wfrest 库
    // 6. 创建 MySQL响应报文体, 全部结果集以 json 格式返回
    httpServer.GET("/mysqljsonall", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        string name = req->query("username");
        cout << name << endl;
        
        string url("mysql://xiao:xiao060@localhost:3306");
        string query("select * from cloudisk.tbl_user_token");
        resp->MySQL(url, query);
    });
    
    // MySQL 使用方法 2
    // NOTE: wfrest v0.9.3 存在问题, 需要修改 wfrest 库
    // 7. 创建 MySQL响应报文体, 返回部分结果集
    httpServer.GET("/mysqljsonpart", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        string name = req->query("username");
        cout << name << endl;
        
        string url = "mysql://xiao:xiao060@localhost:3306";
        string query = "select * from cloudisk.tbl_user_token";
        resp->MySQL(url, query, [resp](wfrest::Json* pJson){
            // cout << pJson->dump() << endl;
            string str = (*pJson)["result_set"]["rows"][0][1];
            resp->String(str);
        });
    });

    // MySQL 使用方法 3
    // 8. 创建 MySQL响应报文体, 使用 结果集迭代器
    httpServer.GET("/mysqlcursor", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        
        string url = "mysql://xiao:xiao060@localhost:3306";
        string query = "select * from cloudisk.tbl_user_token";
        resp->MySQL(url, query, [resp](protocol::MySQLResultCursor* cursor){

            std::vector<std::vector<protocol::MySQLCell>> rows; 
            cursor->fetch_all(rows);

            string str = rows[0][2].as_string();
            cout << "str: " << str << endl;
            resp->String(str);
        });
    });

    // 9. 在 wfrest 中使用 序列 访问 MySQL 
    httpServer.GET("/series_mysql", 
    [](const wfrest::HttpReq* req, wfrest::HttpResp* resp, SeriesWork* series){
        string uri = "mysql://xiao:xiao060@localhost";
        WFMySQLTask* mysqlTask =  WFTaskFactory::create_mysql_task(uri, 1, [resp](WFMySQLTask* mysqlTask){

            protocol::MySQLResponse* mysqlResp = mysqlTask->get_resp(); 
            protocol::MySQLResultCursor cursor(mysqlResp);

            vector<vector<protocol::MySQLCell>> rows;
            cursor.fetch_all(rows);
            string str = rows[1][1].as_string();
            resp->String(str);
        });

        string query = "select * from cloudisk.tbl_user_token";
        mysqlTask->get_req()->set_query(query);
        series->push_back(mysqlTask);
    });


    // 10. 在 wfrest 中使用 序列, 搭配 定时器任务 使用
    // NOTE:定时器任务 不是 网络任务
    // 每个请求方法都 有一个三参数版本, 第3个参数即为 序列Series
    httpServer.GET("/series_timer", 
    [](const wfrest::HttpReq * , wfrest::HttpResp * resp, SeriesWork * series){

        // 定时器 任务
        auto timerTask = WFTaskFactory::create_timer_task(3000 * 1000, 
        [resp](WFTimerTask * ){
            printf("timerCallback is running.\n");
            resp->String("series Timer test");
        });
        //将创建好的定时器任务添加到序列中
        series->push_back(timerTask);
    });






    // track() 函数 追踪所有连接, 打印连接信息
    // 格式: [WFREST] 2023-11-09 19:51:45 | 200 | 127.0.0.1 : 37762 | GET | "/login/str" | --
    if (httpServer.track().start(8888) == 0) {
        // 列出 所有路由
        httpServer.list_routes();
        waitGroup.wait();
        httpServer.stop();
    }

    return 0;
}




