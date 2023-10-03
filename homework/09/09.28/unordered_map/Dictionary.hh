#ifndef __DICTIONARY_HPP__
#define __DICTIONARY_HPP__

#include <map>
#include <string>
#include <unordered_map>

using std::unordered_map;
using std::string;

class Dictionary {
public:
    void read(const string& filename);
    void store(const string& filename);
    
private:
    unordered_map<string, int> _map;
};

#endif
