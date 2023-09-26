#include "AndQuery.hh"
#include "BinaryQuery.hh"




AndQuery::AndQuery(const Query& lhs, const Query& rhs, const string& op) 
: BinaryQuery(lhs, rhs, "&") {}


