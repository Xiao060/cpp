#ifndef __QUERYBASE_HPP__
#define __QUERYBASE_HPP__


// 抽象类
#include "QueryResult.hh"
#include "TextQuery.hh"



class QueryBase {

public:
    friend class Query;
   
private:
    virtual QueryResult query(TextQuery&) const = 0;
    // virtual string rep() const = 0;
};





#endif