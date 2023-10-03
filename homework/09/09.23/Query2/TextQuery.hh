#ifndef __TEXTQUERY_HPP__
#define __TEXTQUERY_HPP__

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "QueryResult.hh"

using std::string;
using std::vector;
using std::map;
using std::set;
using std::shared_ptr;
using std::ifstream;
using std::ofstream;


// 用来储存 vector<string> / map<string, set<size_t>>
// 为了减少 资源的拷贝, vector/set 用智能指针共享
class TextQuery {

    // // 设为 友元类, 因为后续 需要通过 
    // friend class Query;

// private:
public:
    // 设为私有, 不能直接创建对象
    TextQuery(ifstream& ifs);

    // 接收查询 word, 返回查询结果 QueryResult
    QueryResult query(const string& word);



    // 用于 debug
    void printToFile(ofstream& ofs);
   
private:
    shared_ptr<vector<string>> _spFileVector;
    map<string, shared_ptr<set<size_t>>> _wordsNoMap;
};


#endif