#ifndef __QUERYBASE_HPP__
#define __QUERYBASE_HPP__


// 抽象类
#include "QueryResult.hh"
#include "TextQuery.hh"
class QueryBase {
   
public:
   
private:
    virtual QueryResult eval(TextQuery&) {
        
    }
   
};




#endif