#ifndef __MYTASK_HPP__
#define __MYTASK_HPP__

#include "TcpConnection.hh"
#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::shared_ptr;
using std::cout;
using std::endl;


class MyTask {
    using TcpConnectionPtr = shared_ptr<TcpConnection>;

public:
    MyTask(const string& msg, const TcpConnectionPtr& con) 
    : _msg(msg)
    , _con(con) { }

    void process() {
        _con->sendInLoop("hello " + _msg);
    }
    
    
    
private:
    string _msg;
    TcpConnectionPtr _con;
};

#endif
