#include <iostream>
#include <ostream>
#include <cstring>

using std::cout;
using std::endl;
using std::ostream;

class CowString {
public:
    class CharProxy {
    public:
        CharProxy(CowString& self, size_t idx)        
        : _self(self)
        , _idx(idx) {}

        // 赋值
        char& operator=(char ch);
        // 输出
        friend ostream& operator<<(ostream& os, const CharProxy& rhs);

    private:
        CowString& _self;
        size_t _idx;
    };

public:
    CowString();
    CowString(const char* pstr);
    CowString(const CowString& rhs);
    ~CowString();
    CowString& operator=(const CowString& rhs);
    // char& operator[](size_t idx);
    friend ostream& operator<<(ostream &os, const CowString::CharProxy &rhs);

    CharProxy operator[](size_t idx);

    friend ostream& operator<<(ostream& os, const CowString& rhs);

    const char* c_str() const {
        return _pstr;
    }

    int size() const {
        return strlen(_pstr);
    }

private:
    // char* malloc(const char* pstr = nullptr) {
    //     if (pstr == nullptr) {
    //         return new char[kRefcountLength + 1]() + kRefcountLength;
    //     } else {
    //         return new char[kRefcountLength + strlen(pstr) + 1]() + kRefcountLength;
    //     }
    // }
    char* malloc(const char* pstr = "") {
        return new char[kRefcountLength + strlen(pstr) + 1]() + kRefcountLength;
    }

    void release() {
        decreaseRefcount();
        if (use_count() == 0) {
            delete [] (_pstr - kRefcountLength);
            _pstr = nullptr;
        }
    }

    /*********************************************************/

    int use_count() {
        return *reinterpret_cast<int*> (_pstr - kRefcountLength);
    }

    // 将 初始化引用计数 封装为 1 个函数
    void initRefcount() {
        // 将 char* 强转为 int*
        *reinterpret_cast<int*> (_pstr - kRefcountLength) = 1;
    }

    void increaseRefcount() {
        ++*reinterpret_cast<int*> (_pstr - kRefcountLength);
    }

    void decreaseRefcount() {
        --*reinterpret_cast<int*> (_pstr - kRefcountLength);
    }

private:
    // 引用计数所占空间
    static const int kRefcountLength = 4;
    char* _pstr;
};






// 默认构造, 申请空间 (引用计数 + 空字符)
// 且 将 _pstr 初始化为 字符串首地址
CowString::CowString()
: _pstr(malloc()) {
    initRefcount();
}

CowString::CowString(const char* pstr) 
: _pstr(malloc(pstr)) {
    increaseRefcount();
    strcpy(_pstr, pstr);
}

// 拷贝赋值, 直接让引用计数增加 1
CowString::CowString(const CowString& rhs) 
: _pstr(rhs._pstr) {
    increaseRefcount();
}

/*****************************************/

// 析构函数, 引用计数先减 1, 结果为 0 直接销毁
CowString::~CowString() {
    release();
}

CowString& CowString::operator=(const CowString& rhs) {
    // 考虑自复制
    if (this != &rhs) {
        // 判断引用计数后再决定是否回收
        release();
        // 浅拷贝
        _pstr = rhs._pstr;
        // 引用计数 +1
        increaseRefcount();
    }
    return *this;
}

// but 如果只是希望输出 某个字符, 也会完成深拷贝
// 解决方案: 让返回值为自定义类型, 对该类型进行运算符重载
// char& CowString::operator[](size_t idx) {
//     if (idx < size()) {
        
//         if (use_count() > 1) {
//             decreaseRefcount();
//             // 进行深拷贝
//             char* ptmp = malloc(_pstr);
//             strcpy(ptmp, _pstr);
//             // 改变 _pstr 指向, 初始化引用计数
//             _pstr = ptmp;
//             initRefcount();
//         }

//         return _pstr[idx];
//     }

//     cout << "访问越界" << endl;
//     static char nullchar = '\0';
//     return nullchar;
// }

/***********************************************************/

CowString::CharProxy CowString::operator[](size_t idx) {
    return CharProxy(*this, idx);
}

// 赋值
char& CowString::CharProxy::operator=(char ch) {
    if (_idx < _self.size()) {

        if (_self.use_count() > 1) {
            _self.decreaseRefcount();
            // 进行深拷贝
            char* ptmp = _self.malloc(_self._pstr);
            strcpy(ptmp, _self._pstr);
            // 改变 _pstr 指向, 初始化引用计数
            _self._pstr = ptmp;
            _self.initRefcount();
        }

        // 写操作
        _self._pstr[_idx] = ch;

        return _self._pstr[_idx];
    }

    cout << "访问越界" << endl;
    static char nullchar = '\0';
    return nullchar;
}

// 输出
ostream& operator<<(ostream &os, const CowString::CharProxy &rhs) {
    os << rhs._self._pstr[rhs._idx];
    return os;
}

/******************************************************/

ostream& operator<<(ostream& os, const CowString& rhs) {
    os << rhs._pstr;
    return os;
}


int main(int argc, char* argv[]) {

    CowString s1;
    cout << "s1: " << s1 << endl;

    CowString s2 = s1;
    cout << "s2: " << s2 << endl;

    s2 = "Hello World!";
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    s1 = s2;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    CowString s3 = "Hello C++!";

    return 0;
}




