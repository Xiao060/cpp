#include "BinaryQuery.hh"

BinaryQuery::BinaryQuery(const Query& lhs, const Query& rhs, const string& op) 
: _lhs(lhs)
, _rhs(rhs)
, _op(op) {}