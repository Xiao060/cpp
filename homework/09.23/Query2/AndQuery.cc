#include "AndQuery.hh"
#include "BinaryQuery.hh"
#include "Query.hh"




AndQuery::AndQuery(const Query& lhs, const Query& rhs, const string& op) 
: BinaryQuery(lhs, rhs, "&") {}


QueryResult AndQuery::query(TextQuery& tq) const {

}


