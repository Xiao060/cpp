#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__


// 抽象类
// 1. 含有 纯虚函数
// 2. 构造 / 析构 protected
// 注意 2 不能设为私有, 设为私有 则 派生类 无法访问 基类的 构造/析构函数, 即 派生类 也无法 创建实例对象, 这没有意义


// 禁止 拷贝 / 赋值
// 1. 拷贝 / 赋值 函数 delete
// 1. 拷贝 / 赋值 函数 私有
// 2. 继承 NonCopyable 的类

class NonCopyable {
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
