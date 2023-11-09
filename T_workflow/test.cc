#include <iostream>
using std::cout;
using std::endl;
using std::string;

#include <workflow/WFFacilities.h>
#include <workflow/MySQLResult.h>
#include <workflow/MySQLMessage.h>
#include <wfrest/HttpServer.h>
#include <wfrest/json.hpp>

static WFFacilities::WaitGroup waitGroup(1);

void test0()
{
    using namespace wfrest;
    HttpServer server;

    server.GET("/wfrest/query", [](const HttpReq * req, HttpResp * resp){
        //req->get_request_uri();
        cout << "username: " << req->query("username") << endl;
        auto queryList = req->query_list();
        for(auto query: queryList) {
            cout << query.first << ": " << query.second << endl;
        }
        resp->append_output_body("/wfrest/query");
    });

    server.POST("/wfrest/body", [](const HttpReq * req, HttpResp * resp){
        //req->get_parsed_body();//被抛弃了
        cout << "body: " << req->body() << endl;
        resp->append_output_body("/wfrest/body");
    });

    server.POST("/wfrest/urlencoded", [](const HttpReq * req, HttpResp * resp){
        if(req->content_type() == APPLICATION_URLENCODED) {
            auto formKV = req->form_kv();
            for(auto & elem : formKV) {
                cout << elem.first << ": " << elem.second << endl;
            }
        }
        resp->append_output_body("/wfrest/urlencoded");
    });

    server.GET("/wfrest/json", [](const HttpReq * req, HttpResp * resp){
        if(req->content_type() == APPLICATION_JSON) {
            Json & js = req->json();
            cout << js.dump() << endl;
            resp->String("/wfrest/json");
        }             
    });

    server.GET("/wfrest/formdata", [](const HttpReq * , HttpResp * resp){
        resp->File("index.html");
    });

    server.POST("/wfrest/formdata", [](const HttpReq * req, HttpResp * resp){
        if(req->content_type() == MULTIPART_FORM_DATA) {
            Form & formdata = req->form();
            for(auto elem : formdata) {
                cout << elem.first << ", " 
                     << elem.second.first << ": \n"
                     << elem.second.second << endl;
            }
        }
        resp->String("/wfrest/formdata");
    });

    server.GET("/test", [](const HttpReq * , HttpResp * resp){
        resp->append_output_body("/test");
    });
    
    server.GET("/test1", [](const HttpReq * , HttpResp * resp){
        //resp->append_output_body("/test");
        resp->String("/test1");//生成的响应是字符串
    });

    server.GET("/wfrest/mysqltest0", [](const HttpReq * , HttpResp * resp){
        string url("mysql://root:xiao060@localhost:3306");
        string sql("select * from cloudisk.tbl_user_token");
        resp->MySQL(url, sql);
    });

    server.GET("/wfrest/mysqltest1", [](const HttpReq * , HttpResp * resp){
        string url("mysql://root:1234@localhost:3306");
        string sql("select * from cloudisk.tbl_user_token");
        resp->MySQL(url, sql, [resp](Json * pJson){
           //pJson指向的就是我们的JSON对象的首地址 
            string str = (*pJson)["result_set"][0]["rows"][0][1];
            resp->String(str);
        });
    });

    server.GET("/wfrest/mysqltest2", [](const HttpReq * , HttpResp * resp){
        string url("mysql://root:1234@localhost:3306");
        string sql("select * from cloudisk.tbl_user_token");
        using namespace protocol;
        resp->MySQL(url, sql, [resp](MySQLResultCursor * pcursor){
            //pcursor指向的就是MySQL结果集的迭代器的首地址
            std::vector<std::vector<MySQLCell>> rows; 
            pcursor->fetch_all(rows);
            string str = rows[0][2].as_string();
            cout << "str:" << str << endl;
            resp->String(str);
        });
    });

    server.GET("/wfrest/series", 
    [](const HttpReq * , HttpResp * resp, SeriesWork * series){
        auto timerTask = WFTaskFactory::create_timer_task(1000 * 1000, 
        [resp](WFTimerTask * ){
            printf("timerCallback is running.\n");
            resp->String("series Timer test");
        });
        //将创建好的定时器任务添加到序列中
        series->push_back(timerTask);
    });

    server.GET("/wfrest/mysqltest3", 
    [](const HttpReq*, HttpResp * resp, SeriesWork * series){
        string url("mysql://root:1234@localhost:3306");
        string sql("select * from cloudisk.tbl_user_token");
        using namespace protocol;
        auto mysqlTask = WFTaskFactory::create_mysql_task(url, 1, 
        [resp](WFMySQLTask * mysqltask){
            //0. 对任务的状态进行检测
            //1....
            auto mysqlResp = mysqltask->get_resp();
            MySQLResultCursor cursor(mysqlResp);
            std::vector<std::vector<MySQLCell>> rows;
            cursor.fetch_all(rows);
            string str = rows[1][1].as_string();
            resp->String(str);
        });
        mysqlTask->get_req()->set_query(sql);
        series->push_back(mysqlTask);
    });

    server.GET("/wfrest/redistest", [](const HttpReq * , HttpResp * resp){
        string url("redis://localhost");
        string command("SET");
        std::vector<string> params{"guanyu", "39"};
        resp->Redis(url, command, params);
    });



    server.GET("/login", [](const HttpReq * , HttpResp * resp){
        resp->File("postform.html");
    });

    if(server.track().start(8888) == 0) {
        server.list_routes();
        waitGroup.wait();
    } else {
        printf("Server start failed!\n");
    }
}


int main()
{
    test0();
    return 0;
}

