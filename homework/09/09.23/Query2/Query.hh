#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "QueryBase.hh"
#include <memory>


using std::shared_ptr;

class Query {
   
public:

    // Query(const Query& q);

    Query(const string& word);

    QueryResult query(TextQuery& tq) const;

    // 重载 与/或/非 运算符
    Query operator&(const Query& rhs);
    Query operator|(const Query& rhs);
    Query operator~();
    
    
private:
    shared_ptr<QueryBase> _spQueryBase;
};





#endif