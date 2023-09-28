#include "Dictionary.hh"
#include <bits/types/cookie_io_functions_t.h>
#include <cctype>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::endl;


// 只记录 单词 出现次数, 不记录 数字
void Dictionary::read(const string& filename) {
    ifstream ifs(filename);

    string word;
    while (ifs >> word) {
        // 去除 单词前面的 符号 与 数字
        while (word.size() && (ispunct(word.front()) || isdigit(word.front()))) {
            word = word.substr(1);
        }

        // 去除 单词后面的 符号 与 数字
        while (word.size() && (ispunct(word.back()) || isdigit(word.back()))) {
            word = word.substr(0, word.size()-1);
        }

        // 大写转小写
        for (int i = 0; i < word.size() && isupper(word[i]); ++i) {
            word[i]  = tolower(word[i]);
        }

        // 从后往前, 防止中间出现 - 
        for (int i = word.size()-1; i >= 0 && isupper(word[i]); --i) {
            word[i]  = tolower(word[i]);
        }

        if (word.size() == 0) {
            continue;
        }

        auto it = _map.find(word);
        if (it == _map.end()) {
            _map[word] = 1;
        } else {
            ++ it->second;
        }
    }

    ifs.close();
}

void Dictionary::store(const string& filename) {

    ofstream ofs(filename);

    for (auto& elem : _map) {
        ofs << elem.first << ": " << elem.second << endl;
    }


    ofs.close();
}