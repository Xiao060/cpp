#include <cstddef>
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
    static Student* getInstance() {
        if (_pInstance == nullptr) {
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

    void destory() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    // 单例对象自动释放 2
    // 建立一个内部类, 其析构函数 释放 外部类对象
    // 外部类 添加静态成员 内部类对象
    // 可以正常使用 destory
    class AutoRelease {
    public:
        ~AutoRelease() {
            if (_pInstance) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

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
    static AutoRelease _ar;
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
Student::AutoRelease Student::_ar;

int main(int argc, char* argv[]) {

    Student* s1 = Student::getInstance();
    cout << s1 << endl;

    s1->init(1001, 12, "XiaoMing");
    cout << *s1 << endl;
    
    return 0;
}




