#include "query.hh"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::make_shared;
using std::set_intersection;
using std::inserter;

TextQuery::TextQuery(ifstream& ifs) 
: _lines(new vector<string>) {

    string line;
    string word;
    int line_num = 0;

    while (getline(ifs, line)) {

        ++line_num;
        _lines->push_back(line);

        istringstream iss(line);
        while (iss >> word) {
            // 完成了单词头尾 数字/符号 的去除, 但是也会将 纯数字 去除
            // 完成了单词 大写转小写

            // 去除 单词头部 的 数字/符号
            while (word.size() && (ispunct(word[0]) || isdigit(word[0]))) {
                // 截取 子串, 参数1: 开始位置; 参数2: 截取长度, 默认截取到末尾
                word = word.substr(1);
            }

            // 去除 单词尾部 的 数字/符号
            while (word.size() && (ispunct(word.back()) || isdigit(word.back()))) {
                word = word.substr(0, word.size()-1);
            }

            // 大写 转换为 小写 (从前往后转)
            for (int i = 0; i < word.size() && isupper(word[i]); ++i) {
                word[i] = tolower(word[i]);
            }

            // 大写 转换为 小写 (从后往前转)
            for (int i = word.size()-1; i > 0 && isupper(word[i]); --i) {
                word[i] = tolower(word[i]);
            }

            if (word.size() == 0) {
                continue;
            }

            if (_wordNumbers.count(word)) {
                _wordNumbers[word]->insert(line_num);
            } else {
                shared_ptr<set<line_no>> tmp(new set<line_no>);
                tmp->insert(line_num);
                _wordNumbers[word] = tmp;
            }
        }
    }
}

// const 修饰 成员函数(函数体), 不能在函数体中修改数据成员
// 故 函数体内没法使用 _wordNumbers[word]
QueryResult TextQuery::query(const string& word) const {

    // 查找不到 word 时返回的 QueryResult 指向该集合
    static shared_ptr<set<line_no>> emptySet(new set<line_no>);

    // 类型为 map<string, shared_ptr<set<line_no>>>::const_iterator 
    auto pair = _wordNumbers.find(word);
    if (pair != _wordNumbers.end()) {
        return QueryResult(word, _lines, pair->second);
    } else {
        return QueryResult(word, _lines, emptySet);
    }
}

/*************************************************************************/

QueryResult::QueryResult(string word, shared_ptr<vector<string>> lines, shared_ptr<set<line_no>> lineNoSet) 
: _word(word) 
, _lines(lines)
, _lineNoSet(lineNoSet) {}

ostream& print(ostream& os, const QueryResult& rhs) {
    os << rhs._word << " occurs " << rhs._lineNoSet->size() << " "
       << (rhs._lineNoSet->size() > 1 ? "time" : "times") << endl;

    for (auto no : *rhs._lineNoSet) {
        os << "    (line " << no << ") " << (*rhs._lines)[no-1] << endl;
    }

    return os;
}

/**********************************************************************/

void runQueries(ifstream& ifs) {
    TextQuery tq(ifs);

    while (true) {
        cout << "enter word to look for, or q to quit: ";

        string word;
        if (!(cin >> word) || word == "q") {
            break;
        }

        print(cout, tq.query(word)) << endl;
    }
}

/*******************************************************************/

Query::Query(const string& word) 
: _query_base(new WordQuery(word)) {}

ostream& operator<<(ostream& os, const Query& query) {
    return  os << query.rep();
}

/*******************************************************************/

Query operator~(const Query& query) {
    return shared_ptr<QueryBase> (new NotQuery(query));
}

QueryResult NotQuery::eval(const TextQuery& text) const {
    // 获取 单独 2 个行号集合
    auto result = _query.eval(text);

    auto lineNoSet = make_shared<set<line_no>> ();
    auto beg = result.begin();
    auto end = result.end();

    auto sz = result.get_file()->size();
    for (size_t i=1; i < sz+1; ++i) {

        if (beg == end || *beg != i) {
            lineNoSet->insert(i);
        } else if (beg != end) {
            ++beg;
        }
    }

    return QueryResult(rep(), result.get_file(), lineNoSet);
}

/*******************************************************************/

Query operator&(const Query& lhs, const Query& rhs) {
    return shared_ptr<QueryBase> (new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery& text) const {
    // 获取 单独 2 个行号集合
    auto right = _rhs.eval(text);
    auto left = _lhs.eval(text);

    // 求 交集
    // make_shared 返回一个指定类型的 智能指针
    auto lineNoSet = make_shared<set<line_no>> ();
    // set_intersection 求交集, 参数分别为 开始1/结束1/开始2/结束2/目的位置
    // inserter 构造 插入迭代器, 参数分别为 容器/开始插入位置
    set_intersection(left.begin(), left.end(), 
                     right.begin(), right.end(), 
                     inserter(*lineNoSet, lineNoSet->begin()));
    
    return QueryResult(rep(), left.get_file(), lineNoSet);
}

/*******************************************************************/


Query operator|(const Query& lhs, const Query& rhs) {
    return shared_ptr<QueryBase> (new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& text) const {
    // 获取 单独 2 个行号集合
    auto right = _rhs.eval(text);
    auto left = _lhs.eval(text);

    // 求并集
    // make_shared 返回一个指定类型的 智能指针
    auto lineNoSet = make_shared<set<line_no>> (left.begin(), left.end());
    lineNoSet->insert(right.begin(), right.end());
    
    return QueryResult(rep(), left.get_file(), lineNoSet);
}







