#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include <fstream>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
using std::set;
using std::ifstream;
// vector 长度的类型, 即 size_t
using line_no = vector<string>::size_type;

// 前向声明
class QueryResult;

class TextQuery {
public:
    // 构造函数, 传入文件流, 完成 数据成员的初始化
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
   
private:
    // 储存每一行文件内容
    shared_ptr<vector<string>> _lines;
    map<string, shared_ptr<set<line_no>>> _wordNumbers;
};






class QueryBase {
   
protected:
    
   
private:
    // 纯虚函数, 设为私有 ???
    virtual QueryResult eval(const TextQuery&) = 0;
    virtual string rep() const = 0;

   
};

class WordQuery 
: public QueryBase {
   
public:
   
private:
   
};

class NotQuery 
: public  QueryBase {
   
public:
   
private:
   
};

class BinaryQuery 
: public QueryBase {
   
public:
   
private:
   
};

class AndQuery 
: public BinaryQuery {
   
public:
   
private:
   
};

class OrQuery 
: public BinaryQuery {
   
public:
   
private:
   
};



#endif