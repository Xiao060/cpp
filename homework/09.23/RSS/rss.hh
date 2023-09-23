#ifndef __RSS_HPP__
#define __RSS_HPP__

#include <string>
#include <vector>

using std::string;
using std::vector;

struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

class RssReader {
public:
    // RssReader();
    void parseRss();//解析
    void dump(const string & filename);//输出
private:
    vector<RssItem> _rss;
};   

#endif