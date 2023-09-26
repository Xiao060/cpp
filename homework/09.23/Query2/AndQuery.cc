#include "AndQuery.hh"
#include "BinaryQuery.hh"
#include "Query.hh"
#include "QueryResult.hh"
#include <algorithm>
#include <set>

using std::set_intersection;


AndQuery::AndQuery(const Query& lhs, const Query& rhs, const string& op) 
: BinaryQuery(lhs, rhs, "&") {}


QueryResult AndQuery::query(TextQuery& tq) const {
    QueryResult qr1 = _lhs.query(tq);
    QueryResult qr2 = _lhs.query(tq);

    set_intersection(qr1.)
}


