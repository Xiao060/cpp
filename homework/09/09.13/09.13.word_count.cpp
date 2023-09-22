#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>


using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;

struct Record {
	string _word;
	int _frequency;
};

class Dictionary {
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};

void Dictionary::read(const string& filename) {
    
    ifstream ifs(filename);
    if (!ifs.good()) {
        cerr << "fail to open file" << endl;
        return ;
    }

    string word;
    while (ifs >> word) {
        if (isdigit(word.back()) || ispunct(word.back())) {
            continue;
        }

        auto beg = _dict.begin();
        auto end = _dict.end();
        auto mid = beg + (end - beg) / 2;
    
        while (mid != end) {
            if (word == (*mid)._word) {
                break;
            } else if (word < (*mid)._word) {
                end = mid;
            } else {
                beg = mid + 1;
            }
            mid = beg + (end - beg) / 2;
        }

        if (mid != end) {
            ++(*mid)._frequency;
        } else {
            _dict.insert(mid, {word, 1});
        }
    }

    ifs.close();
}

void Dictionary::store(const string& filename) {
    ofstream ofs(filename);

    for (auto i : _dict) {
        ofs << i._word << ": " << i._frequency << endl;
    }

    ofs.close();
}


int main(int argc, char* argv[]) {

    Dictionary dict;

    dict.read("The_Holy_Bible.txt");
    dict.store("count.txt");

    return 0;
}




