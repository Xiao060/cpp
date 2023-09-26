#ifndef __BINARY_QUERY_HPP__
#define __BINARY_QUERY_HPP__

#include "Query.hh"
#include <memory>

using std::shared_ptr;

class BinaryQuery {
   
public:

private:
    BinaryQuery(const Query& lhs, const Query& rhs, const string& op);
   
private:
    Query _lhs, _rhs;
    string _op;
};





#endif