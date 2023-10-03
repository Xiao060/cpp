#ifndef __ANDQUERY_HPP__
#define __ANDQUERY_HPP__

#include "BinaryQuery.hh"
#include "Query.hh"
#include "QueryResult.hh"
#include "TextQuery.hh"


class AndQuery 
: public BinaryQuery {
   
public: 
    friend class Query;

private:
    AndQuery(const Query& lhs, const Query& rhs, const string& op);
   
    QueryResult query(TextQuery& tq) const;
};




#endif