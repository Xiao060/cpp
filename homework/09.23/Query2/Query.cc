#include "Query.hh"
#include "WordQuery.hh"

// 需要访问 WordQuery 的 构造函数
// 1. 构造函数 设为 public ------------> 可以通过 WordQuery 直接创建对象   ×
// 2. 构造私有, Query 设为 friend -----> √
Query::Query(const string& word)
: _spQuery(new WordQuery(word)) {} 


// 需要访问 QueryBase(派生类) 的 query 函数
// 同上 两种情况
QueryResult Query::query(TextQuery& tq) const {
    return _spQuery->query(tq);
}