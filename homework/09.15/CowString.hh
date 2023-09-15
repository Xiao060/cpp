#ifndef __COWSTRING_HPP__
#define __COWSTRING_HPP__

#include <cstring>
#include <ostream>

using std::ostream;

class CowString {
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






    // 获取 引用计数
    int use_count();

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