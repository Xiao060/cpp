#include "TextQuery.hh"
#include "QueryResult.hh"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <utility>
#include <vector>

using std::istringstream;
using std::pair;
using std::endl;

TextQuery::TextQuery(ifstream& ifs) 
: _spFileVector(new vector<string>) {

    string line;
    string word;
    size_t no = 0;

    while (getline(ifs, line)) {

        // 行号 +1, 该行 入 数组
        ++no;
        _spFileVector->push_back(line);

        istringstream iss(line);
        while (iss >> word) {

            // 去除 word 前面的字母 符号, 此处不考虑纯数字的情况
            while (word.size() && (ispunct(word[0]) || isdigit(word[0]))) {
                word = word.substr(1);
            }

            // 去除 word 后面的字母 符号, 此处不考虑纯数字的情况
            while (word.size() && (ispunct(word.back()) || isdigit(word.back()))) {
                word = word.substr(0, word.size() - 1);
            }

            if (word.size() == 0) {
                continue;
            }

            // 大写转小写, 考虑到有可能存在连字符, 且连字符两侧均为 大写
            // 故 该转换 分为 `头 -> 尾` 与 `尾 -> 头` 两步
            for (int i = 0; i < word.size() && isupper(word[i]); ++i) {
                word[i] = tolower(word[i]);
            }

            for (int i = word.size()-1; i >= 0 && isupper(word[i]); --i) {
                word[i] = tolower(word[i]);
            }

            auto it = _wordsNoMap.find(word);
            if (it != _wordsNoMap.end()) {
                // 存在, 则向 set 中 添加 no
                it->second->insert(no);
            } else {
                // 不存在, 则 向 map 添加 pair
                shared_ptr<set<size_t>> sp(new set<size_t>);
                sp->insert(no);
                _wordsNoMap.insert(pair<string, shared_ptr<set<size_t>>> (word, sp));
                // 下列方式也可
                // _wordsNoMap.insert({word, sp});
            }
        }
    }
}


QueryResult TextQuery::query(const string& word) {

    static shared_ptr<set<size_t>> retSet;
    
    auto it = _wordsNoMap.find(word);
    if (it == _wordsNoMap.end()) {
        return QueryResult(word, _spFileVector, retSet);
    }

    return QueryResult(word, _spFileVector, it->second);
}

void TextQuery::printToFile(ofstream& ofs) {

    for (auto& elem : _wordsNoMap) {
        ofs << elem.first << ": "  << elem.second->size() << endl;
    }

}