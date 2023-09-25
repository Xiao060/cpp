#include "WordQuery.hh"


QueryResult WordQuery::query(TextQuery& tq) const {
    return tq.query(word);
}