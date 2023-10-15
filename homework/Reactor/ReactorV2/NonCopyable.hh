#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__


// 禁止 拷贝/赋值
// 1. 拷贝/赋值 私有
// 2. 拷贝/赋值 delete
// 3. 继承 一个 NonCopyable 的类, 此类 不能直接创建对象
//    为了禁止 NonCopyable 构造对象, 构造/析构 需要设为 protected
//    为了 禁止 派生类 拷贝/赋值, 需要把 NonCopyable 的 拷贝/赋值 设为私有 或 delete

class NonCopyable {
    
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
