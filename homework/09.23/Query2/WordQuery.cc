#include "WordQuery.hh"


WordQuery::WordQuery(const string& word) 
: _word(word) {}


QueryResult WordQuery::query(TextQuery& tq) const {
    return tq.query(_word);
}