#ifndef __REPLACE_HPP__
#define __REPLACE_HPP__

#include <string>
#include <unordered_map>


using std::unordered_map;
using std::string;


class Replace {

public:

    void read_map(const string& filename);

    void replace(const string& filename);

    
    
private:
    unordered_map<string, string> _map;
};

#endif
