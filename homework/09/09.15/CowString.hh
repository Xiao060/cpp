#ifndef __COWSTRING_HPP__
#define __COWSTRING_HPP__

#include <cstring>
#include <ostream>

using std::ostream;

class CowString {

public:

    // 若直接在 CowString 内定义成员函数, 返回 char&, 则无法区分 R / W
    class CharProxy {
    public:
        CharProxy(CowString& self, size_t idx);
        
        // 重载 类型转换函数, 使 CharProxy 可以直接输出 而 不用 重载 <<  
        operator char();

        // 重载 赋值运算符函数
        char& operator=(char ch);

    private:
        CowString& _self;
        int _idx;
    };

public:
    // 构造函数
    // 1.无参构造, 则必须分配空间, 初始化 引用计数
    // 2.C字符串 构造, 必须分配空间, 初始化 引用计数
    // 3.CowString 构造, 不必分配空间, 引用计数 +1
    CowString();
    CowString(const char* lhs);
    CowString(const CowString& lhs);

    // 析构函数
    ~CowString();

    /*****************************************************/

    // 重载 赋值运算符 (CowString 对象版)
    CowString& operator=(const CowString& lhs);

    // 重载 输出运算符 (友元)
    friend ostream& operator<<(ostream& os, const CowString& rhs);

    /******************************************************/

    // 重载 取下标运算符, 返回值为 CharProxy 对象
    CharProxy operator[](size_t idx);
    
    // 获取 引用计数
    int use_count();

    // 获取字符串长度
    int size();

private:
    // 分配空间
    char* malloc(const char* lhs = "");

    // 释放, 引用计数 先 -1, 若结果为 0 则释放空间
    void release();

    // 初始化引用计数 
    void initRefcount();

    // 引用计数 +1
    void increaseRefcount();

    // 引用计数 -1
    void decreaseRefcount();

private:
    char* _pstr;
    // 引用计数 所占字节数
    static const int RefcountLenght = 4;
};



#endif