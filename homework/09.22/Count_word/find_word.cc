#include "find_word.hh"
#include <bits/types/FILE.h>
#include <cstdio>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

TextQuery::TextQuery() 
: _lines(new vector<string>) {}


// 删除器, fstream
struct FSTREAMCloser {
    void operator()(ifstream* ptr) {
        if (ptr) {
            ptr->close();
        }
    }
};
    
void TextQuery::readFile(const string filename) {
    FSTREAMCloser fc;
    ifstream ifs(filename);

    shared_ptr<ifstream> sp(&ifs, fc);

    string line;
    int line_num = 0;
    while (getline(ifs, line)) {
        ++line_num;
        _lines->push_back(line);

        istringstream iss(line);

        string word;
        while (iss >> word) {
             // 去除 单词头尾的 数字/符号, but 纯数字 也会被 去除
            while (word.size() && (ispunct(word[0]) || isdigit(word[0]))) {
                word = word.substr(1);
            }

            while (word.size() && (ispunct(word.back()) || isdigit(word.back()))) {
                word = word.substr(0, word.size() - 1);
            }

            if (!word.size()) {
                continue;
            }

            // 将单词转换为 小写
            // but Shenzhen-HK 不会转 - 后面的, 即 shenzhen-HK
            for (int i=0; i < word.size() && isupper(word[i]); ++i) {
                word[i] = tolower(word[i]);
            }
            
            if (_word2Numbers.count(word)) {
                _word2Numbers[word]->insert(line_num);
            } else {
                shared_ptr<set<int>> tmp(new set<int>);
                tmp->insert(line_num);
                _word2Numbers[word] = tmp;
            }
        }
    }
}



// QueryResult 
void TextQuery::query(const string &word) {
    cout << "------------------------------------------------------------------------------------------" << endl;

    if (_word2Numbers.count(word)) {
        cout << word << " occurs " << _word2Numbers[word]->size() << " times." << endl;

        for (auto i : *_word2Numbers[word]) {
            cout << "    (line " << i << ") " << (*_lines)[i-1] << endl;
        }
    } else {
        cout << word << " occurs 0 times." << endl;
    }

    cout << "------------------------------------------------------------------------------------------" << endl;

}