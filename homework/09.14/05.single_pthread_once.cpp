#include <cstddef>
#include <iostream>
#include <cstring>
#include <ostream>
#include <pthread.h>

using std::cout;
using std::endl;
using std::ostream;

// 单例模式
// 1.构造/析构私有, 拷贝/赋值 delete, 静态变量 指向该类的指针
// 2.静态函数 getInstance, 返回指向该类的指针
// 3.初始化 init / 回收 destory 函数
class Student {
public:
    
    // 因为 pthread_once 只能保证函数执行一次, 故若单例对象被手动销毁便无法再创建
    // 解决方案: destory 私有, 禁止手动调用
    static Student* getInstance() {
        pthread_once(&_once, init_r);
        return _pInstance;
    }

    void init(int num, int age, const char* name) {
        _pInstance->_num = num;
        _pInstance->_age = age;
        delete [] _pInstance->_name;
        _pInstance->_name = new char[strlen(name) + 1]();
        strcpy(_pInstance->_name, name);
    }

    friend ostream& operator<<(ostream& os, const Student& stu);
    friend ostream& operator<<(ostream& os, const Student* stu);

    Student(const Student&) = delete;
    Student& operator=(const Student& ) = delete;

private:
    Student(int num = -1, int age = -1, const char* name = "NULL")
    : _num(num)
    , _age(age)
    , _name(new char[strlen(name) + 1]()) {
        strcpy(_name, name);
    }

    ~Student() {
        delete [] _name;
        _name = nullptr;
    }

    // 将 构造 与 注册 destory 定义为一个单独函数
    // 使用 pthreadd_once 使它们只能执行一次
    // 且该函数也应设为 私有, 否则可以通过手动调用创建出多个堆上的对象
    static void init_r() {
        _pInstance = new Student();
        atexit(destory);
    }

    static void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    int _num;
    int _age;
    char* _name;
    static Student* _pInstance;
    // 为 pthread_once 的第一个参数准备
    static pthread_once_t _once;
};

ostream &operator<<(ostream &os, const Student &stu) {
    os << "num: " << stu._num << endl
       << "age: " << stu._age << endl
       << "name: " << stu._name;

    return os;
}

ostream &operator<<(ostream &os, const Student* stu) {
    os << "num: " << stu->_num << endl
       << "age: " << stu->_age << endl
       << "name: " << stu->_name;

    return os;
}






Student* Student::_pInstance = nullptr;
pthread_once_t Student::_once = PTHREAD_ONCE_INIT;

int main(int argc, char* argv[]) {

    Student* s1 = Student::getInstance();
    cout << s1 << endl;

    s1->init(1001, 12, "XiaoMing");
    cout << *s1 << endl;

    return 0;
}




