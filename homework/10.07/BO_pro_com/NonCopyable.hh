#ifndef __NONCOPYABLE_HPP__
#define __NONCOPYABLE_HPP__


// 禁止 拷贝/赋值
// 1. 拷贝/赋值 设为 private
// 2. 拷贝/赋值 delete
// 3. 继承 NonCopyable

// 此处 保证 NonCopyable 不能创建对象, 且其派生类可以创建对象
// 构造/析构 需要设为 保护
class NonCopyable {
protected:
    NonCopyable() = default;
    virtual ~NonCopyable() = default;
    
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif
