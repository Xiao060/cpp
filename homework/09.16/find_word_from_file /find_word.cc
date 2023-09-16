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

    string line;
    while (getline(ifs, line)) {
        _lines.push_back(line);

        istringstream iss(line);

        string word;
        while (iss >> word) {
            
            while (word.size() && ispunct(word[0])) {
                word = word.substr(1);
            }

            while (word.size() && ispunct(word.back())) {
                word = word.substr(0, word.size() - 1);
            }

            if (word.size()) {
                cout << word << endl;
            }

        }



    }



}



void TextQuery::query(const string & word) {

}