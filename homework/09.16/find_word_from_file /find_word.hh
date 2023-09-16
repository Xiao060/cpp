#ifndef __FIND_WORD_HPP__
#define __FIND_WORD_HPP__

#include <string>
#include <vector>
#include <map>
#include <set>

using std::string;
using std::vector;
using std::map;
using std::set;

class TextQuery {
public:
    void readFile(const string filename);
    void query(const string & word);//

private:
    vector<string> _lines;//O(1)
    map<string, set<int> > _wordNumbers;//the the
    map<string, int> _dict;//
};



#endif