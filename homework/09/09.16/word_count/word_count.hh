#ifndef __WORD_COUNT_HPP__
#define __WORD_COUNT_HPP__

#include <string>
#include <map>

using  std::map;
using std::string;

class Record {
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    map<string, int> _dict;
};

#endif