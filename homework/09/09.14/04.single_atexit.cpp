#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ostream>

using std::cout;
using std::endl;
using std::ostream;

// 单例模式
// 1.构造/析构私有, 拷贝/赋值 delete, 静态变量 指向该类的指针
// 2.静态函数 getInstance, 返回指向该类的指针
// 3.初始化 init / 回收 destory 函数
class Student {
public:
    // 单例模式自动释放 3
    // atexit 注册函数, 被注册的函数在进程结束时会自动执行
    // 注册的函数 是 静态函数
    // but 多线程时可能同时进入 if, 创建多个对象
    static Student* getInstance() {
        if (_pInstance == nullptr) {
            atexit(destory);
            _pInstance = new Student();
        }

        return _pInstance;
    }

    void init(int num, int age, const char* name) {
        _pInstance->_num = num;
        _pInstance->_age = age;
        delete [] _pInstance->_name;
        _pInstance->_name = new char[strlen(name) + 1]();
        strcpy(_pInstance->_name, name);
    }

    static void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
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

    int _num;
    int _age;
    char* _name;
    static Student* _pInstance;
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

int main(int argc, char* argv[]) {

    Student* s1 = Student::getInstance();
    cout << s1 << endl;

    s1->init(1001, 12, "XiaoMing");
    cout << *s1 << endl;
    
    // Student::destory();
    // s1->destory();
    return 0;
}




