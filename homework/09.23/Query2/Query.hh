#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include "QueryBase.hh"
#include <memory>


using std::shared_ptr;

class Query {
   
public:

    Query(const string& word);

    QueryResult query(TextQuery& tq) const;
    
   
private:
    shared_ptr<QueryBase> _spQuery;
};





#endif