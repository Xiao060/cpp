#include "Query.hh"
#include "AndQuery.hh"
#include "WordQuery.hh"
#include <memory>

// Query::Query(const Query& q) 
// : _spQueryBase(q._spQueryBase) {}


// 需要访问 WordQuery 的 构造函数
// 1. 构造函数 设为 public ------------> 可以通过 WordQuery 直接创建对象   ×
// 2. 构造私有, Query 设为 friend -----> √
Query::Query(const string& word)
: _spQueryBase(new WordQuery(word)) {} 


// 需要访问 QueryBase(派生类) 的 query 函数
// 同上 两种情况
QueryResult Query::query(TextQuery& tq) const {
    return _spQueryBase->query(tq);
}

Query Query::operator&(const Query& rhs) {
    return AndQuery()    
}

Query Query::operator|(const Query& rhs) {

}

Query Query::operator~() {

}