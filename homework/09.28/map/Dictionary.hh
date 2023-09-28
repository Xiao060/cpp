#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <map>
#include <string>

using std::map;
using std::string;

class Dictionary {
public:
    void read(const string& filename);
    void store(const string& filename);
    
private:
    map<string, int> _map;
};

#endif
