
#include <csignal>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>


#include <workflow/MySQLMessage.h>
#include <workflow/WFFacilities.h>
#include <workflow/WFGlobal.h>
#include <workflow/WFTask.h>
#include <workflow/WFTaskFactory.h>
// 获取 响应报文 类型的枚举值
#include <workflow/mysql_types.h>
#include <workflow/MySQLResult.h>





using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;



WFFacilities::WaitGroup waitGroup(1);

void handler(int signum) {
    waitGroup.done();
}


void mysqlCallback(WFMySQLTask* mysqlTask) {

    // 1. 检测 连接状态
    int state = mysqlTask->get_state();
    int error = mysqlTask->get_error();
    if (state != WFT_STATE_SUCCESS) {
        cout << WFGlobal::get_error_string(state, error);
        return;
    }

    // 2. 检测 sql 语句执行效果
    // 若失败, 1. sql语句格式错误; 2. sql执行错误
    // 获取 响应报文 
    protocol::MySQLResponse* resp = mysqlTask->get_resp();
    int type = resp->get_packet_type();
    if (type == MYSQL_PACKET_ERROR) {
        int errorCode = resp->get_error_code();
        string errorMsg = resp->get_error_msg();
        cout << "ERROR " << errorCode << ": " << errorMsg << endl;
        return;
    }


    // 3. 判断是 读操作 还是 写操作, 根据操作执行对应的 处理
    // 获取 结果集
    protocol::MySQLResultCursor cursor(resp);
    int cursorStatus = cursor.get_cursor_status();
    if (cursorStatus == MYSQL_STATUS_OK) {
        // 写操作
        // NOTE: 写操作获取行数使用 get_affected_rows() 函数
        unsigned long long rowsNum = cursor.get_affected_rows();
        cout << "Query OK, " << rowsNum << (rowsNum > 1 ? " rows " : " row ") << "affected" << endl;
    } else if (cursorStatus == MYSQL_STATUS_GET_RESULT) {
        // 读操作
        // NOTE: 读操作获取 行数 使用 get_rows_count() 函数
        unsigned long long rowsNum = cursor.get_rows_count();
        cout << rowsNum << (rowsNum > 1 ? " rows " : " row ") << "in set" << endl;

        // 获取 列数
        int fieldsNum = cursor.get_field_count();
        const protocol::MySQLField* const* fields = cursor.fetch_fields();

        for (int i = 0; i < fieldsNum; ++i) {
            // cout << fields[i]->get_name() << "\t";
            printf("%-20s", fields[i]->get_name().c_str());
        }
        cout << endl;

        // for (int i = 0; i < fieldsNum; ++i) {
        //     cout << fields[i]->get_length() << "    ";
        // }
        // cout << endl;

        // for (int i = 0; i < fieldsNum; ++i) {
        //     cout << fields[i]->get_data_type() << "    ";
        // }
        // cout << endl;

        // 获取一行数据
        // 1. 储存在 vector 中
        // vector<protocol::MySQLCell> row;
        // cursor.fetch_row(row);
        // for (auto& elem : row) {
        //     if (elem.is_int()) {
        //         cout << elem.as_int() << "    ";
        //     } else if (elem.is_string()) {
        //         cout << elem.as_string() << "    ";
        //     }
        // }
        // cout << endl;
        // 2. 储存在 map 中, k为 列名, v为 值
        // map<string, protocol::MySQLCell> row;
        // cursor.fetch_row(row);
        // for (auto& elem : row) {
        //     cout << elem.first << ": ";
        //     if (elem.second.is_int()) {
        //         cout << elem.second.as_int() << endl;
        //     } else if (elem.second.is_string()) {
        //         cout << elem.second.as_string() << endl;
        //     }
        // }
        // 3. 储存在 unordered_map 中, k为 列名, v为 值
        // ...

        // 获取所有数据
        vector<vector<protocol::MySQLCell>> rows;
        cursor.fetch_all(rows);

        for (auto& row : rows) {
            for (auto& elem : row) {
                if (elem.is_int()) {
                    //cout << elem.as_int() << "\t";
                    printf("%-20d", elem.as_int());
                } else if (elem.is_string()) {
                    //cout << elem.as_string() << "\t";
                    printf("%-20s", elem.as_string().c_str());
                }
            }
            cout << endl;
        }

    }

    // 4. 读操作
    // if (cursorStatus == mysql_stat) {
        
    // }



    waitGroup.done();
}



int main(int argc, char* argv[]) {

    signal(SIGINT, handler);

    // 1. 创建 mysql 任务
    WFMySQLTask* mysqlTask = WFTaskFactory::create_mysql_task("mysql://xiao:xiao060@localhost:3306",
                                                                1,
                                                                mysqlCallback);

    // 2. 设置 mysql任务的属性
    // string query = "insert into cloudisk.tbl_user_token(user_name, user_token)" \
                                                "values('LiuBei', 'LiuBei_aaa')";
    string query = "select * from cloudisk.tbl_user_token";
    mysqlTask->get_req()->set_query(query);

    // 3. 启动 mysql任务
    mysqlTask->start();

    waitGroup.wait();
    return 0;
}




