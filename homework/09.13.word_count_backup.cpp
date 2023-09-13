#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
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

    // vector<Record>::iterator 
    vector<Record>::iterator binary_find(const string word);
private:
    vector<Record> _dict;
};

void Dictionary::read(const string& filename) {

    _dict.push_back({"AAA", 12});
    _dict.push_back({"BBB", 13});
    _dict.push_back({"CCC", 14});
    _dict.push_back({"DDD", 15});
    

    ifstream ifs(filename);
    string word;
    while (ifs >> word) {
        cout << word << endl;


        auto test = binary_find(word);
        cout << "iterator: " << (*test)._word << ": " 
                             << (*test)._frequency << endl;

    }

    ifs.close();
}

void Dictionary::store(const string& filename) {

}

vector<Record>::iterator Dictionary::binary_find(const string word) {
    auto beg = _dict.begin();
    auto end = _dict.end();
    auto mid = beg + (end - beg) / 2;

    while (mid != end) {
        if (word == (*mid)._word) {
            return mid;
        } else if (word < (*mid)._word) {
            end = mid;
        } else {
            beg = mid - 1;
        }
        mid = beg + (end - beg) / 2;
    }
    return end;
}

int main(int argc, char* argv[]) {

    Dictionary dict;

    dict.read("test.txt");


    return 0;
}




