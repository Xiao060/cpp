#include "rss.hh"
#include "tinyxml2.h"
#include <iostream>

using tinyxml2::XMLDocument;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;
using std::cout;
using std::endl;

//解析
void RssReader::parseRss() {
    XMLDocument doc;
    doc.LoadFile("coolshell.xml");

    if (doc.Error()) {
        cout << "Error: failed to open xml document!" << endl;
    }
    cout << "success to open xml document!" << endl;


    // xml 结构 
    // rss -> channel -> item1/itme2/item3/...


    // 获取根节点, 即 rss
    // 此处使用 doc.FirstChildElement() 也可以
    XMLElement* root = doc.RootElement();
    cout << "01: " << root->Value() << endl;
    
    // XMLElement* elem = doc.FirstChildElement();
    // cout << "01: " << elem->Value() << endl;

    // 获取 channel
    XMLElement* channel = root->FirstChildElement();
    cout << "02: " << channel->Value() << endl;

    // 获取 item 
    XMLElement* elem;
    
    elem = channel->FirstChildElement("item");
    cout << "03: " << elem->Value() << endl;

    elem = elem->FirstChildElement("title");
    cout << "04: " << elem->Value() << ": " 
         << elem->GetText() << endl;

    elem = elem->NextSiblingElement("link");
    cout << "05: " << elem->Value() << ": "
         << elem->GetText() << endl;

    elem = elem->NextSiblingElement("description");
    cout << "06: " << elem->Value() << ": "
         << elem->GetText() << endl;

    cout << "***************************************" << endl;

    elem = elem->NextSiblingElement("content:encoded");
    cout << "07: " << elem->Value() << ": "
         << elem->GetText() << endl;

    // item = item->NextSiblingElement("item");
    // cout << "04: " << item->Value() << endl;
    // cout << item->GetText() << endl;
    


    // cout << x->ToElement()->Value() << endl;

    // XMLElement* elem = doc.FirstChildElement();
    // cout << "02: " << elem->Value() << endl;

    // elem = elem->NextSiblingElement();
    // cout << "03: " << elem->Value() << endl;

    

    // x = x->FirstChild();
    // cout << "05: " << x->Value() << endl;

    // x = x->NextSibling();
    // cout << x->Value() << endl;

    // x = x->LastChild();
    // cout << x->Value() << endl;

    // x = x->LastChild();
    // cout << x->Value() << endl;

    // x = x->LastChild();
    // cout << x->Value() << endl;
}



//输出
void RssReader::dump(const string & filename) {

}
