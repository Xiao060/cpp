#ifndef __BINARY_QUERY_HPP__
#define __BINARY_QUERY_HPP__

#include "Query.hh"
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class BinaryQuery {

public:
    friend class Query;
    
protected:
    BinaryQuery(const Query& lhs, const Query& rhs, const string& op);
   
    Query _lhs, _rhs;
    string _op;
};





#endif