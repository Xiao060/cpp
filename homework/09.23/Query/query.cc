#include "query.hh"
#include <cctype>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::istringstream;
using std::string;
using std::endl;

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
            while (word.size() && ispunct(word[0]) || isdigit(word[0])) {
                // 截取 子串, 参数1: 开始位置; 参数2: 截取长度, 默认截取到末尾
                word = word.substr(1);
            }

            // 去除 单词尾部 的 数字/符号
            while (word.size() && ispunct(word.back()) || isdigit(word.back())) {
                word = word.substr(0, word.size()-1);
            }

            // 大写 转换为 小写 (从前往后转)
            for (int i = 0; isupper(word[i]) && i < word.size(); ++i) {
                word[i] = toupper(word[i]);
            }

            // 大写 转换为 小写 (从后往前转)
            for (int i = word.size()-1; isupper(word[i]) && i > 0; --i) {
                word[i] = toupper(word[i]);
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

QueryResult::QueryResult(string word,shared_ptr<vector<string>> lines, shared_ptr<set<line_no>> lineNoSet) 
: _word(word) 
, _lines(lines)
, _lineNoSet(lineNoSet) {}

ostream& print(ostream& os, const QueryResult& rhs) {
    os << rhs._word << " occurs " << rhs._lineNoSet->size() << " "
       << (rhs._lineNoSet->size() > 1 ? "time" : "times") << endl;

    for (auto no : *rhs._lineNoSet) {
        os << "\t(line " << no << " ) " << (*rhs._lines)[no-1] << endl;
    }

    return os;
}

/**********************************************************************/

















