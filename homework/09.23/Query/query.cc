#include "query.hh"
#include <cctype>
#include <memory>
#include <sstream>
#include <vector>

using std::istringstream;

TextQuery::TextQuery(ifstream& ifs) 
: _lines(new vector<string>) {

    string line;
    string word;
    int line_no = 0;
    while (getline(ifs, line)) {

        ++line_no;
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
            



        }







    }

}



QueryResult TextQuery::query(const string&) const {

}