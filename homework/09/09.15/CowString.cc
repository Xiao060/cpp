#include "CowString.hh"
#include <cstring>
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
    if (this != &lhs) {
        release();
        _pstr = lhs._pstr;
        increaseRefcount();
        cout << "CS赋值" << endl;
    }
    return *this;
}


// 重载 输出运算符 (友元)
ostream& operator<<(ostream& os, const CowString& rhs) {
    os << rhs._pstr;
    return os;
}

// 获取字符串长度
int CowString::size() {
    return strlen(_pstr);
}

/******************************************************************/

// CharProxy 内部类构造函数
CowString::CharProxy::CharProxy(CowString& self, size_t idx)
: _self(self)
, _idx(idx) {}

// 类型转换函数 
CowString::CharProxy::operator char() {
    //检查是否越界
    if (_idx < _self.size()) {
        return _self._pstr[_idx];
    }

    cout << "访问越界";
    static char nullchar = '\0';
    return nullchar;
}

// 重载 赋值运算符函数
char& CowString::CharProxy::operator=(char ch) {
    // 判断索引 是否 越界
    if (_idx < _self.size()) {

        // 引用计数 == 1, 直接修改
        // 引用计数 > 1, 则 引用计数 -1 ----> 深拷贝 ----> 初始化引用计数
        if (_self.use_count() > 1) {
            _self.decreaseRefcount();

            char* ptmp = _self.malloc(_self._pstr); 
            strcpy(ptmp, _self._pstr);

            _self._pstr = ptmp;
            _self.initRefcount();
        }
        
        _self._pstr[_idx] = ch;
        return _self._pstr[_idx];
    }

    // 越界, 返回 nullchar
    cout << "访问越界" << endl;
    static char nullchar = '\0';
    return nullchar;
}
    
// CowString 重载 取下标运算符, 返回值为 CharProxy 对象 (成员函数)
CowString::CharProxy CowString::operator[](size_t idx) {
    return CharProxy(*this, idx);
}





