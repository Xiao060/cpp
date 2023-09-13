#include "string.hh"
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ostream>
#include <string>

using std::string;

// 无参构造
String::String() 
: _pstr(new char[1]()) {
    *_pstr = '\0';
}

// C 字符串构造
String::String(const char* str)
: _pstr(new char[strlen(str) + 1]()) {
    strcpy(_pstr, str);
}

// 拷贝构造
String::String(const String& str)
: _pstr(new char[str.size() + 1]) {
    strcpy(_pstr, str.c_str());
}

// 析构函数
String::~String() {
    delete [] _pstr;
}

// 重载赋值运算符 (String 类)
String& String::operator=(const String& s) {
    if (s != *this) {
        delete [] _pstr;
        _pstr = new char[s.size() + 1]();
        strcpy(_pstr, s.c_str());
    }
    return *this;
}

// 重载赋值运算符 (C 字符串)
String& String::operator=(const char* s) {
    delete [] _pstr;
    _pstr = new char[strlen(s) + 1]();
    strcpy(_pstr, s);
    return *this;
}

// 重载 += (String 类)
String& String::operator+=(const String& s) {
    if (s.size() == 0) {
        return *this;
    }

    char* p = new char[size() + s.size() + 1]();
    strcpy(p, _pstr);
    strcat(p, s.c_str());

    delete [] _pstr;
    _pstr = p;
    return *this;
}


// 重载 += (C 字符串)
String& String::operator+=(const char* s) {
    if (strlen(s) == 0) {
        return *this;
    }

    char* p = new char[size() + strlen(s) + 1]();
    strcpy(p, _pstr);
    strcat(p, s);

    delete [] _pstr;
    _pstr = p;
    return *this;
}

// 重载下标访问运算符 []
char& String::operator[](size_t index) {
    return _pstr[index];
}

const char& String::operator[](size_t index) const {
    return _pstr[index];
}

// 获取字符串长度
size_t String::size() const {
    return strlen(_pstr);
}

// 转换为 C 字符串
const char* String::c_str() const {
    return _pstr;
}

/*******************************************************************/
// 以下为 友元函数

// 重载 ==
bool operator==(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) == 0 ? true : false;
}

// 重载 !=
bool operator!=(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) != 0 ? true : false;
}

// 重载 <
bool operator<(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) < 0 ? true : false;
}

// 重载 <=
bool operator<=(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) <= 0 ? true : false;
}

// 重载 >
bool operator>(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) > 0 ? true : false;
}

// 重载 >=
bool operator>=(const String& s1, const String& s2) {
    return strcmp(s1.c_str(), s2.c_str()) >= 0 ? true : false;
}

// 重载 输出运算符 << 
std::ostream& operator<<(ostream& os, const String& s) {
    os << s._pstr;
    return os;
}

// 重载 输入运算符 >>  
std::istream& operator>>(istream& is, String& s) {
    char tmp[1024] = {0};
    is.getline(tmp, sizeof(tmp));
    s = tmp;
    return is;
}

// 重载 + 
String operator+(const String& s1, const String& s2) {
    char* p = new char[s1.size() + s2.size() + 1]();
    sprintf(p, "%s%s", s1.c_str(), s2.c_str());

    String s(p);
    delete [] p;
    return  s;
}

String operator+(const String& s1, const char* s2) {
    char* p = new char[s1.size() + strlen(s2) + 1]();
    sprintf(p, "%s%s", s1.c_str(), s2);

    String s(p);
    delete [] p;
    return  s;
}

String operator+(const char* s1, const String& s2) {
    char* p = new char[strlen(s1) + s2.size() + 1]();
    sprintf(p, "%s%s", s1, s2.c_str());

    String s(p);
    delete [] p;
    return  s;
}




















