#include "Replace.hh"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

void Replace::read_map(const string& filename) {
    ifstream ifs(filename);

    string key;
    string value;
    while (ifs >> key, getline(ifs, value)) {
            _map[key] = value.substr(1);
    }

    ifs.close();
}


void Replace::replace(const string& filename) {
    ifstream ifs(filename);

    string line;
    string word;

    while (getline(ifs, line)) {

        istringstream iss(line);
        while (iss >> word) {
            auto it = _map.find(word);
            if (it == _map.end()) {
                cout << word << " ";
            } else {
                cout << it->second << " ";
            }
        }
        cout << endl;
    }

    ifs.close();
}

