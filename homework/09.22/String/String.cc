#include <cstring>
#include <iostream>
#include "String.hh"

using std::cin;
using std::cout;
using std::endl;

String::String() 
: _data(nullptr) {
    cout << "String()" << endl;
}

String::String(const char* rhs) 
: _data(new char[strlen(rhs) + 1]()) {
    strcpy(_data, rhs);
    cout << "String(const char*)" << endl;
}

String::String(const String& rhs) 
: _data(new char[strlen(rhs._data) + 1]()) {
    strcpy(_data, rhs._data);
    cout << "String(const String&)" << endl;
}

String::String(String&& rhs) 
: _data(rhs._data) {
    rhs._data = nullptr; 
    cout << "String(String&&)" << endl;
}

String::~String() {
    if (_data) {
        delete [] _data;
        _data = nullptr;
    }
    cout << "~String()" << endl;
}

String& String::operator=(const String& rhs) {
    cout << "operator=(const String&)" << endl;
    // 1. 考虑自复制
    if (this != &rhs) {
        // 2. 释放空间
        delete [] _data;
        // 3. 深拷贝
        _data = new char[strlen(rhs._data) + 1]();
        strcpy(_data, rhs._data);
    }
    // 4. 返回 *this
    return *this;
}

String& String::operator=(String&& rhs) {
    cout << "operator=(String&&)" << endl;
    // 1. 考虑自复制
    if (this != &rhs) {
        // 2. 释放空间
        delete [] _data;

        // 3. 浅拷贝
        _data = rhs._data;
        rhs._data = nullptr;
    }
    // 4. 返回 *this
    return *this;
}

ostream& operator<<(ostream& os, const String& rhs) {
    if (rhs._data) {
        os << rhs._data;
    }
    return os;
}


