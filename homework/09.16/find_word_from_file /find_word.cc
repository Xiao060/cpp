#include "find_word.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::istringstream;


void TextQuery::readFile(const string filename) {

    ifstream ifs(filename);

    if (!ifs.good()) {
        cerr << "Fail to open file!" << endl;
        return ;
    }

    int line_num = 0;
    string line;
    while (getline(ifs, line)) {
        ++line_num;
        _lines.push_back(line);

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
            
            if (_dict.count(word)) {
                _dict[word] += 1;
                _wordNumbers[word].insert(line_num);
            } else {
                _dict[word] = 1;
                _wordNumbers[word] = {line_num};
            }
        }
    }

    ifs.close();
}



void TextQuery::query(const string & word) {

    cout << "------------------------------------------------------------------------------------------" << endl;

    if (_dict.count(word)) {
        cout << word << " occurs " << _dict[word] << " times." << endl;

        for (auto i : _wordNumbers[word]) {
            cout << "(line " << i << ") " << _lines[i-1] << endl;
        }
    } else {
        cout << word << " occurs 0 imes." << endl;
    }

    cout << "------------------------------------------------------------------------------------------" << endl;

}