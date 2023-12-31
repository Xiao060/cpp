#include <cstddef>
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

class String {
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print();
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

// 初始化为 '\0', 打印时不必判断
String::String() 
: _pstr(new char[1]()) {}

String::String(const char* pstr) 
: _pstr(new char[strlen(pstr) + 1]()){
    strcpy(_pstr, pstr);
}

String::String(const String& rhs) 
: _pstr(new char[strlen(rhs._pstr) + 1]()){
    strcpy(_pstr, rhs._pstr);
}

// 赋值运算符
// 考虑自复制 -> 回收 -> 申请空间 -> 深拷贝
String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        delete [] _pstr;
        _pstr = new char[strlen(rhs._pstr) + 1]();
        strcpy(_pstr, rhs._pstr);
    }
    return *this;
}

String::~String() {
    delete [] _pstr;
}

size_t String::length() const {
    return strlen(_pstr);
}

void String::print() {
    cout << _pstr << endl;
}

const char* String::c_str() const {
    return _pstr;
}

int main() {
	String str1;
	str1.print();

	String str2 = "Hello,world";
	String str3("wangdao");
	
	str2.print();		
	str3.print();	
	
	String str4 = str3;
	str4.print();
	
	str4 = str2;
	str4.print();
	
	return 0;
}


