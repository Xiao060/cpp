#ifndef __FIND_WORD_HPP__
#define __FIND_WORD_HPP__

#include <ostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <memory>
#include <iostream>

using std::string;
using std::vector;
using std::set;
using std::map;
using std::shared_ptr;
using std::ostream;

class TextQuery {
public:
    TextQuery();
    
    void readFile(const string filename);
    // QueryResult 
    void query(const string &word);
     
private:
    shared_ptr<vector<string>> _lines; 
    map<string, shared_ptr<set<int>> > _word2Numbers;
};

// void print(ostream & os, const QueryResult &);

#endif