#include "find_word.hh"
#include <fstream>
#include <iostream>
#include <string>

using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

void TextQuery::readFile(const string filename) {
    ifstream ifs(filename);

    if (!ifs.good()) {
        cerr << "Fail to open file!" << endl;
        return ;
    }

    string line;
    while (getline(ifs, line)) {
        _lines.push_back(line);
    }

    ifs.close();
}

void TextQuery::query(const string & word) {
    for (int i=0; i < _lines.size(); ++i) {

        // cout << _lines[i] << endl;

        size_t n = _lines[i].find(word);
        if (n != string::npos) {
            cout << "(line " << i+1 << ") " << _lines[i] << endl;
        }
    }
}