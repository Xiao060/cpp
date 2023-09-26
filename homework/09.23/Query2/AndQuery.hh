#ifndef __ANDQUERY_HPP__
#define __ANDQUERY_HPP__

#include "BinaryQuery.hh"
#include "Query.hh"


class AndQuery 
: public BinaryQuery {
   
public:

    AndQuery(const Query& lhs, const Query& rhs, const string& op);
   
private:


   
};




#endif