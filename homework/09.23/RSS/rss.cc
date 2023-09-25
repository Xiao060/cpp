#include "rss.hh"
#include "tinyxml2.h"
#include <iostream>
#include <regex>
#include <fstream>

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using std::cout;
using std::endl;
using std::regex;
using std::regex_replace;
using std::ofstream;

// xml 结构 
// rss -> channel -> item1/itme2/item3/...

//解析
void RssReader::parseRss() {
    // 加载 xml 文件
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");

    if (doc.Error()) {
        cout << "Error: failed to open xml document!" << endl;
    }

    // 获取根节点, 即 rss
    // 此处使用 doc.FirstChildElement() 也可以
    // XMLElement* elem = doc.FirstChildElement();
    XMLElement* root = doc.RootElement();

    // 获取 channel
    XMLElement* channel;
    channel = root->FirstChildElement();

    // 获取 item
    XMLElement* item;
    item = channel->FirstChildElement("item");
    
    // 获取 item 内部元素 title/link/descrption/content:encoded
    XMLElement* elem;
    string text;
    regex e("<[\\s\\S]+?>");
    // regex e("<.*?>");

    // ofstream ofs("c.txt");

    while (item) {
        RssItem ritem;

        elem = item->FirstChildElement("title");
        text = elem->GetText();
        text = regex_replace(text, e, "");
        ritem.title = text;

        elem = elem->NextSiblingElement("link");
        text = elem->GetText();
        text = regex_replace(text, e, "");
        ritem.link = text;

        elem = elem->NextSiblingElement("description");
        text = elem->GetText();
        text = regex_replace(text, e, "");
        ritem.description = text;

        elem = elem->NextSiblingElement("content:encoded");
        text = elem->GetText();
        text = regex_replace(text, e, "");
        ritem.content = text;

        // ofs << text << endl;

        _rss.push_back(ritem);

        item = item->NextSiblingElement();
    }

}



//输出
void RssReader::dump(const string & filename) {
    ofstream ofs(filename);

    int docid = 0;
    for (auto item : _rss) {
        ++docid;
        ofs << "<doc>" << endl;
        ofs << "    <docid>" << docid << "</docid>" << endl;
        ofs << "    <title>" << item.title << "</title>" << endl;
        ofs << "    <link>" << item.link << "</link>" << endl;
        ofs << "    <description>" << item.description << "</description>" << endl;
        ofs << "    <content>" << item.content << "</content>" << endl;
        ofs << "</doc>" << endl;
        ofs << endl;
    }

    ofs.close();
}
