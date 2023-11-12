#include <iostream>
#include <string>
#include <unistd.h>
#include <crypt.h>

#include <vector>
#include <workflow/WFFacilities.h>
#include <workflow/WFMySQLServer.h>
#include <wfrest/HttpMsg.h>
#include <workflow/MySQLMessage.h>
#include <workflow/MySQLResult.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
#include <workflow/Workflow.h>
#include <workflow/mysql_types.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

WFFacilities::WaitGroup waitgroup(1);


void mysqlLoginQueryCallback(WFMySQLTask* mysqlTask) {

    // 1. 检测连接状态
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error) << endl;
        return;
    }


    // 2. 检测 SQL 语句
    protocol::MySQLResponse* resp = mysqlTask->get_resp();
    int type = resp->get_packet_type();
    cout << type << endl;
    // if (type != MYSQL_PACKET_GET_RESULT) {
    //     cout << "无查询结果!" << endl;
    //     return;
    // }

    // 获取 mysql 中的 user_pwd
    protocol::MySQLResultCursor cursor(resp);
    vector<protocol::MySQLCell> row;
    cursor.fetch_row(row);
    string user_pwd = row[0].as_string();
    cout << "user_pwd: " << user_pwd << endl;

    // if (encodedPasswd != user_pwd) {
    //     cout << "encodedPasswd: " << encodedPasswd << endl;
    //     cout << "user_pwd: " << user_pwd << endl;
    //     httpResp->String("ERROR");
    //     return;
    // }
}


int main(int argc, char* argv[]) {

    string uri = "mysql://xiao:xiao060@localhost:3306/cloudisk";
    string query = "select user_pwd from tbl_user where user_name = 'xiao060'";

    cout << query << endl;
    WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task(uri, 1, mysqlLoginQueryCallback);
    mysqlTask->get_req()->set_query(query);
    mysqlTask->start();

    waitgroup.wait();

    return 0;
}




