#include "CowString.hh"
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;



// 分配空间, lhs 默认为空字符串
char* CowString::malloc(const char* lhs) {
    return new char[RefcountLenght + strlen(lhs) + 1]() + RefcountLenght;
}

// 释放, 引用计数 -1, 若结果为 0, 则释放空间
void CowString::release() {
    decreaseRefcount();
    if (use_count() == 0) {
        delete [] (_pstr - RefcountLenght);
        _pstr = nullptr;
        cout << "释放空间" << endl;
    }
}

// 初始化引用计数 
void CowString::initRefcount() {
    *reinterpret_cast<int*>(_pstr - RefcountLenght) = 1;
}

// 引用计数 +1
void CowString::increaseRefcount() {
    ++ *reinterpret_cast<int*>(_pstr - RefcountLenght);
}

// 引用计数 -1
void CowString::decreaseRefcount() {
    -- *reinterpret_cast<int*>(_pstr - RefcountLenght);
}

// 获取 引用计数
int CowString::use_count() {
    return *reinterpret_cast<int*>(_pstr - RefcountLenght);
}


/*********************************************************/

// 1.无参构造, 则必须分配空间, 初始化 引用计数
CowString::CowString() 
: _pstr(malloc()) {
    initRefcount();
    cout << "无参构造" << endl;
}

// 2.C字符串 构造, 必须分配空间, 初始化 引用计数
CowString::CowString(const char* lhs)
: _pstr(malloc(lhs)) {
    initRefcount();
    strcpy(_pstr, lhs);
    cout << "C 构造" << endl;
}

// 3.CowString 构造, 不必分配空间, 引用计数 +1
CowString::CowString(const CowString& lhs) 
: _pstr(lhs._pstr) {
    increaseRefcount();
    cout << "CS构造" << endl;
}

// 析构函数, 引用计数 先 -1, 若结果为 0 则释放空间
CowString::~CowString() {
    release();
    cout << "析构函数" << endl;
}


/**************************************************************************/

// 重载 赋值运算符 (CowString 对象版), 先释放原有内容, 指针指向新内容, 引用计数 +1
CowString& CowString::operator=(const CowString& lhs) {
    release();
    _pstr = lhs._pstr;
    increaseRefcount();
    cout << "CS赋值" << endl;
    return *this;
}


// 重载 输出运算符 (友元)
ostream& operator<<(ostream& os, const CowString& rhs) {
    os << rhs._pstr;
    return os;
}






