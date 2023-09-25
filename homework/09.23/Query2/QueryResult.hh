#ifndef __QUERY_RESULT_HPP__
#define __QUERY_RESULT_HPP__


#include <cstddef>
#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <string>
#include <vector>



using std::string;
using std::shared_ptr;
using std::vector;
using std::set;
using std::ofstream;


class QueryResult {

public:

    QueryResult(string word, shared_ptr<vector<string>> spFileVector, shared_ptr<set<size_t>> spWordNoSet);

    // 用于 debug
    void printToFile(ofstream& ofs);
   
private:
    string _word;
    shared_ptr<vector<string>> _spFileVector;
    shared_ptr<set<size_t>> _spWordNoSet;
};




#endif