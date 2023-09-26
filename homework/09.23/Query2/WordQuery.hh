#ifndef __WORDQUERY_HPP__
#define __WORDQUERY_HPP__

#include "Query.hh"
#include "QueryBase.hh"
#include "QueryResult.hh"
#include "TextQuery.hh"
#include <string>

class WordQuery
: public QueryBase {
   
public:

    // 将 Query 设为 友元类, 通过 Query 创建 WordQuery
    friend class Query;

   
private:
    // 构造函数设为 私有, 禁止直接调用
    WordQuery(const string& word);

    // 从 QueryBase 继承过来的
    QueryResult query(TextQuery& tq) const;
    string words() const;

private:
    string _word;
};




#endif
