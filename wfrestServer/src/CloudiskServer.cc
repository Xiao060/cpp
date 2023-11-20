#include "CloudiskServer.hh"
#include "token.hh"

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <unistd.h>
#include <vector>

#include <wfrest/HttpMsg.h>
#include <wfrest/Json.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::bind;
using namespace std::placeholders;
using std::vector;

struct RespPasswd {
    string username;
    string encodedPasswd;
    wfrest::HttpResp* resp;
    CloudiskServer* th;
};


void CloudiskServer::handler(int signum) {
    _waitGroup.done();
}


CloudiskServer::CloudiskServer(int n) 
: _httpServer() 
, _waitGroup(n) { }



void CloudiskServer::loadStaticResourceModule() {
    // 1. GET 请求 注册 
    _httpServer.GET("/signup", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        resp->File("../static/view/signup.html");
    });

    // 2. GET 请求 登陆
    _httpServer.GET("/signin", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        resp->File("../static/view/signin.html");
    });

    // 3. home
    _httpServer.GET("/home", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        resp->File("../static/view/home.html");
    });

    // 4. auth.js
    _httpServer.GET("/static/js/auth.js", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        resp->File("../static/js/auth.js");
    });

    // 5. avatar.jpeg
    _httpServer.GET("/static/img/avatar.jpeg", [](const wfrest::HttpReq* req, wfrest::HttpResp* resp){
        resp->File("../static/img/avatar.jpeg");
    });

}


void CloudiskServer::loadUserRegisterModule() {
    _httpServer.POST("/signup", [this](const wfrest::HttpReq* req, wfrest::HttpResp* resp, SeriesWork* series){

        // 1. 解析请求, 获取 用户名/密码
        map<string, string> formKV = req->form_kv();
        string username = formKV["username"];
        string password = formKV["password"];

        // 2. 对 密码 使用盐值 加密
        // 使用 crypt 函数对 密码加密
        // 第 1 个参数为 密码; 
        // 第 2 个参数为 盐值, 使用随机算法生成
        // 返回值为 char*
        // Linux 密码保存在 /etc/shadow 中
        // 格式: 用户名:密码:...; 密码格式: @哈希算法@salt@密文
        // xiao:
        // $6
        // $2iOt7nhEkwS23GEH
        // $GKZUOnd/B3cGnNj0Vy3ZTF98oc2Sz59EY27aCb30gyTH71aB5pNMdLAaOiIr28j9kHyyMJj1U2VZ0X8fpSHn//:
        // 19600:0:99999:7:::
        // 盐值一般使用随机算法生成
        string salt = "12345678";
        string encodedPasswd = crypt(password.c_str(), salt.c_str());

        // 3. 写入数据库
        // 4. 生成响应报文 SUCCESS / ERROR
        string uri = "mysql://xiao:xiao060@localhost:3306/cloudisk";
        string query = "INSERT INTO tbl_user(user_name, user_pwd) VALUES('";
        query += username + "', '" + encodedPasswd + "');";

        WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(uri, 1, bind(&CloudiskServer::mysqlRegisterCallback, this, _1));
        mysqlTask->get_req()->set_query(query);
        mysqlTask->user_data = resp;
        series->push_back(mysqlTask);
    });
}



void CloudiskServer::loadUserLoginModule() {
    _httpServer.POST("/signin", [this](const wfrest::HttpReq* req, wfrest::HttpResp* resp, SeriesWork* series){
        // 1. 获取请求, 得到 用户名/密码, 并计算加密密文
        map<string, string> formKV = req->form_kv();
        string username = formKV["username"];
        string password = formKV["password"];

        string salt = "12345678";
        string encodedPasswd = crypt(password.c_str(), salt.c_str());

        // 2. 将 加密密文 与 mysql tbl_user 中的密文 比对
        // 不相等 则 生成响应报文, 返回 ERROR
        // 相等 则 生成 token, 存入 tbl_user_token; 
        // 并生成响应报文 返回 json, 格式 {"data":{"Username":..., "Token":..., "Location":...}}
        string uri = "mysql://xiao:xiao060@localhost:3306/cloudisk";
        string query = "select user_pwd from tbl_user where user_name = '" + username + "'";
        // cout << query << endl;
        WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(uri, 1, bind(&CloudiskServer::mysqlLoginReadCallback, this, _1));
        mysqlTask->get_req()->set_query(query);

        // 设置 共享数据
        RespPasswd* tmp = new RespPasswd();
        tmp->username = username;
        tmp->encodedPasswd = encodedPasswd;
        tmp->resp = resp;
        tmp->th = this;
        series->set_context(tmp);

        series->push_back(mysqlTask);

    });
}



void CloudiskServer::loadUserInfoModule() {
    _httpServer.GET("/user/info", [this](const wfrest::HttpReq* req, wfrest::HttpResp* resp, SeriesWork* series){
        // 1. 解析请求, 获取 用户名/token
        // 此处 信息位于 get 请求中的 查询词中, 使用 req->query() 获取
        string username = req->query("username");
        string token = req->query("token");

        // 2. 查询数据库, 获取用户登录时间
        string url = "mysql://xiao:xiao060@localhost:3306/cloudisk";
        WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(url, 1, 
                            bind(&CloudiskServer::mysqlUserInfoCallback, this, _1));
        string query = "select user_name, signup_at from tbl_user where user_name = '"
                        + username + "'";
        // 设置共享数据
        mysqlTask->user_data = resp;
        mysqlTask->get_req()->set_query(query);
        series->push_back(mysqlTask);
    });
}


void CloudiskServer::loadFileQueryModule() {
    _httpServer.POST("/file/query", [this](const wfrest::HttpReq* req, wfrest::HttpResp* resp, SeriesWork* series){

        // 1. 获取请求信息
        string username = req->query("username");
        string limit = req->form_kv()["limit"];

        string url = "mysql://xiao:xiao060@localhost:3306/cloudisk";
        WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(url, 1, );
        string query = "select file_name, file_size, file_sha1, upload_at, last_update from tbl_user_file where user_name = '" + username + "' limit " + limit;
        mysqlTask->get_req()->set_query(query);
        series->push_back(mysqlTask);
    });
}




void CloudiskServer::start(unsigned short port) {

    // 追踪 所有 连接
    if (_httpServer.track().start(port) == 0) {
        // 列出 已有路由
        _httpServer.list_routes();
        _waitGroup.wait();
    } else {
        cout << "CloudiskServer start failed!" << endl;
    }
}


/*********************************************************************************/
/*                                  MySQL 回调函数                               */
/*********************************************************************************/

void CloudiskServer::mysqlRegisterCallback(WFMySQLTask* mysqlTask) {
    // 获取 http 响应
    wfrest::HttpResp* httpResp = (wfrest::HttpResp*) mysqlTask->user_data;

    // 1. 状态检测
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        httpResp->String("ERROR");
        cout << WFGlobal::get_error_string(state, error) << endl;
        return;
    }

    // 2. 检测 SQL 语句
    // 获取响应
    protocol::MySQLResponse* resp = mysqlTask->get_resp();
    int type = resp->get_packet_type();
    if (type != MYSQL_PACKET_OK) {
        cout << "Error " << resp->get_error_code() << ": " << resp->get_error_msg() << endl;
        httpResp->String("ERROR");
    } else {
        httpResp->String("SUCCESS");
    }
}


void CloudiskServer::mysqlLoginReadCallback(WFMySQLTask* mysqlTask) {

    // 获取 http 的 resp 及 加密的密文
    RespPasswd* tmp = (RespPasswd*) series_of(mysqlTask)->get_context();
    wfrest::HttpResp* httpResp = tmp->resp;
    string encodedPasswd = tmp->encodedPasswd;
    string username = tmp->username;
    CloudiskServer* th = tmp->th;

    // 1. 检测连接状态
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error) << endl;
        httpResp->String("ERROR");
        return;
    }


    // 2. 检测 SQL 语句
    // NOTE:注意此处检测的是 packet 的状态
    protocol::MySQLResponse* resp = mysqlTask->get_resp();
    int type = resp->get_packet_type();
    if (type == MYSQL_PACKET_ERROR) {
        cout << "Error " << resp->get_error_code() << ": " << resp->get_error_msg() << endl;
        httpResp->String("ERROR");
        return;
    }

    // 3. 获取 结果集, 即 mysql 中的 user_pwd
    // NOTE:此处检测的是 status 状态
    protocol::MySQLResultCursor cursor(resp);
    if (cursor.get_cursor_status() != MYSQL_STATUS_GET_RESULT) {
        cout << "MySQL 查询出错" << endl;
        httpResp->String("ERROR");
        return;
    }

    vector<protocol::MySQLCell> row;
    cursor.fetch_row(row);
    string user_pwd = row[0].as_string();

    // 密码不同, 登录失败
    if (encodedPasswd != user_pwd) {
        cout << "encodedPasswd != user_pwd" << endl;
        httpResp->String("ERROR");
        return;
    }

    // 登录成功
    // 3.1 生成 token, [用户名 + salt] 加密, 再拼接上时间
    Token t(username, "12345678");
    string token = t.genToken();
    // cout << "token: " << token << endl;

    // 3.2 写入 tbl_user_token 数据库
    string url = "mysql://xiao:xiao060@localhost:3306/cloudisk";
    string query = "REPLACE INTO tbl_user_token(user_name, user_token) Values('";
    query += username + "', '" + token + "')";
    // cout << query << endl;
    // 此处 MySQL 完成的是写入操作, 回调函数非必要
    WFMySQLTask* mysqlTaskWrite = WFTaskFactory::create_mysql_task(url, 1, bind(&CloudiskServer::mysqlLoginWriteCallback, th, _1));
    mysqlTaskWrite->get_req()->set_query(query);
    series_of(mysqlTask)->push_back(mysqlTaskWrite);

    // 3.3 生成响应报文
    wfrest::Json data;
    data["Token"] = token;
    data["Username"] = username;
    data["Location"] = "/home";
    wfrest::Json respMsg;
    respMsg.push_back("data", data);

    // cout << respMsg.dump()  << endl;
    httpResp->String(respMsg.dump());
}
    
    
void CloudiskServer::mysqlLoginWriteCallback(WFMySQLTask* mysqlTask) {
// 1. 检测连接状态
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error) << endl;
        return;
    }


    // 2. 检测 SQL 语句
    // NOTE:注意此处检测的是 packet 的状态
    protocol::MySQLResponse* resp = mysqlTask->get_resp();
    int type = resp->get_packet_type();
    if (type == MYSQL_PACKET_ERROR) {
        cout << "Error " << resp->get_error_code() << ": "
            << resp->get_error_msg() << endl;
        return;
    }

    // 3. 获取 结果集, 即 mysql 中的 user_pwd
    // NOTE:此处检测的是 status 状态
    protocol::MySQLResultCursor cursor(resp);
    if (cursor.get_cursor_status() != MYSQL_STATUS_OK) {
        cout << "MySQL 写入出错" << endl;
        return;
    }
}


void CloudiskServer::mysqlUserInfoCallback(WFMySQLTask* mysqlTask) {

    // 获取 http 响应
    wfrest::HttpResp* resp = (wfrest::HttpResp*) mysqlTask->user_data;

    // 1. 检测连接状态
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error) << endl;
        return;
    }

    // 2. 检测 SQL 语句, 注意次处 使用 MYSQL_PACKET_TYPE
    protocol::MySQLResponse* mysqlResp = mysqlTask->get_resp();
    int type = mysqlResp->get_packet_type();
    if (type == MYSQL_PACKET_ERROR) {
        cout << "Error " << mysqlResp->get_error_code() 
            << ": " << mysqlResp->get_error_msg() << endl;
        return;
    }

    // 3. 获取结果集
    protocol::MySQLResultCursor cursor(mysqlResp);
    vector<protocol::MySQLCell> row;
    cursor.fetch_row(row);
    wfrest::Json data;
    data["Username"] = row[0].as_string();
    // data["SignupAt"] = row[1].as_string();
    data["SignupAt"] = row[1].as_datetime();
    wfrest::Json respMsg;
    respMsg.push_back("data", data);

    // 4. 设置响应报文
    resp->String(respMsg.dump());
}


void CloudiskServer::mysqlFileQueryCallback(WFMySQLTask* mysqlTask) {

}