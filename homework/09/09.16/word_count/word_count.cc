#include <iostream>
#include "word_count.hh"
#include <fstream>
#include <cctype>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

void Record::read(const string &filename) {

    ifstream ofs(filename);

    if (!ofs.good()) {
        cerr << "Fail to open file!" << endl;
        return ;
    }

    string word;
    while (ofs >> word) {

        // 头尾含数字, 直接丢弃
        if (isdigit(word[0]) || isdigit(word.back())) {
            continue;
        }

        // 头尾含标点, 去除标点
        while (word.size() && ispunct(word[0])) {
            word = word.substr(1);
        }

        while (word.size() && ispunct(word.back())) {
            word = word.substr(0, word.size()-1);
        }

        // 判断长度
        if (word.size() == 0) {
            continue;
        }

        // 大写转小写
        for (int i=0; i < word.size() && isupper(word[i]); ++i) {
            word[i] = tolower(word[i]);
        }

        if (_dict.count(word)) {
            _dict[word] += 1;
        } else {
            _dict[word] = 1;
        }
    }

    ofs.close();
}


void Record::store(const string &filename) {
    ofstream ofs(filename);

    // 增强 for 循环 遍历
    for (auto wc : _dict) {
        ofs << wc.first << ": " << wc.second << endl;
    }

    ofs.close();
}
