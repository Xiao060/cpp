#ifndef __String_HPP__
#define __String_HPP__

#include <iostream>
#include <ostream>

using std::ostream;

class String {
public:
    String();
    String(const char*);
    String(const String&);
    String(String&&);
    ~String();

    String& operator=(const String&);
    String& operator=(String&&);

    friend ostream& operator<<(ostream& os, const String& rhs);
private:
    char* _data;
};

#endif