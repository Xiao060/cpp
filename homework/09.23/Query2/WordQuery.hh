#ifndef __WORDQUERY_HPP__
#define __WORDQUERY_HPP__

#include "Query.hh"
#include "QueryBase.hh"
#include "QueryResult.hh"
#include "TextQuery.hh"

class WordQuery
: public QueryBase {
   
public:

    // 将 Query 设为 友元类, 通过 Query 创建 WordQuery
    friend class Query;

   
private:
    // 构造函数设为 私有, 禁止直接调用
    WordQuery(const string& word);

    QueryResult query(TextQuery& tq) const;

private:
    string _word;
};




#endif
