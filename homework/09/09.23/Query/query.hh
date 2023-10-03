#ifndef __QUERY_HPP__
#define __QUERY_HPP__

#include <fstream>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <vector>

using std::string;
using std::shared_ptr;
using std::map;
using std::vector;
using std::set;
using std::ifstream;
using std::ostream;
// vector 长度的类型, 即 size_t
using line_no = vector<string>::size_type;

// 前向声明
class QueryResult;

/******************************************************************************************/

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

/******************************************************************************************/

class QueryResult {
public:
    QueryResult(string s, shared_ptr<vector<string>> lines, shared_ptr<set<line_no>> lineNoSet);

    friend ostream& print(ostream&, const QueryResult&);

    auto begin() {
        return _lineNoSet->begin();
    }

    auto end() {
        return _lineNoSet->end();
    }

    auto get_file() {
        return _lines;
    }
   
private:
    // 要查询的单词
    string _word;
    // 智能指针, 指向 文件内容 
    shared_ptr<vector<string>> _lines;
    // 智能指针, 指向 查询单词对应的
    shared_ptr<set<line_no>> _lineNoSet;
};

/******************************************************************************************/

void runQueries(ifstream&);

/******************************************************************************************/

// 抽象基类, 不希望 用户/派生类 调用 QueryBase, 故没有 public 成员
// 通过 有元函数 Query 去使用 QueryBase
class QueryBase {
friend class Query;

protected:
    virtual ~QueryBase() = default;

private:
    // 纯虚函数

    // 接收 TextQuery, 返回查询后的 QueryResult
    virtual QueryResult eval(const TextQuery&) const = 0;

    // 返回 要查询的 单词
    virtual string rep() const = 0;
};

/******************************************************************************************/

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

    friend ostream& operator<<(ostream&, const Query&);

public:
    Query(const string&);

    // 通过 智能指针成员 使用 QueryBase 的 eval/rep
    QueryResult eval(const TextQuery& t) const {
        return _query_base->eval(t);
    }
    string rep() const {
        return _query_base->rep();
    }

private:
    // 构造函数
    Query(shared_ptr<QueryBase> query_base)
    : _query_base(query_base) {}

private:
    shared_ptr<QueryBase> _query_base;
};

/******************************************************************************************/

class WordQuery 
: public QueryBase {

    friend class Query;

    // 构造函数
    WordQuery(const string& word)
    : _query_word(word) {}

    // 返回 根据 TextQuery 查找 _query_word 后的结果 QueryResult
    QueryResult eval(const TextQuery& t) const {
        return t.query(_query_word);
    }

    // 返回 要查询的 单词
    string rep() const {
        return _query_word;
    }

    // 要查找的单词
    string _query_word;
};

/******************************************************************************************/

class NotQuery 
: public QueryBase {
    
    friend Query operator~(const Query&);
    
    // 构造函数
    NotQuery(const Query& q)
    : _query(q) {}

    QueryResult eval(const TextQuery&) const;
    // 返回要查询的字符串
    string rep() const {
        return "~(" + _query.rep() + ") ";
    }

    Query _query;
};

/******************************************************************************************/

class BinaryQuery 
: public QueryBase {
   
protected:
    // protected

    BinaryQuery(const Query& lhs, const Query& rhs, string op) 
    : _lhs(lhs)
    , _rhs(rhs)
    , _op(op) {}

    // 此处只完成了 1 个虚函数, 剩余 1 个在 派生类中完成
    // 返回 要查询的内容 
    string rep() const {
        return "(" + _lhs.rep() + " " + _op + " " + _rhs.rep() + ")";
    }

    Query _lhs, _rhs;
    string _op;
};

/******************************************************************************************/

class AndQuery 
: public BinaryQuery {
   
   friend Query operator&(const Query&, const Query&);

   AndQuery(const Query& left, const Query& right) 
   : BinaryQuery(left, right, "&") {}

   QueryResult eval(const TextQuery&) const;
   
};

/******************************************************************************************/

class OrQuery 
: public BinaryQuery {
   
    friend Query operator|(const Query&, const Query&);

    OrQuery(const Query& left, const Query& right) 
    : BinaryQuery(left, right, "|") {}

    QueryResult eval(const TextQuery&) const;
};


#endif