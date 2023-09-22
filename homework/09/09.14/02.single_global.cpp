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
    friend class AutoRelease;

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


// 单例模式自动释放 1
// 1.定义友元类, 成员为 指向单例对象的指针
// 2.析构函数 delete 单例对象指针 (调用 单例对象 operator delete / 析构函数 回收资源)
// 3.destory 不能再使用, 否则可能出现 double free
class AutoRelease {
public:
    AutoRelease(Student* pstu) 
    : _pstu(pstu) {}

    ~AutoRelease() {
        if (_pstu) {
            delete _pstu;
            _pstu = nullptr;
        }
    }

private:
    Student* _pstu;
};





Student* Student::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    AutoRelease tmp(Student::getInstance());

    Student* s1 = Student::getInstance();
    cout << s1 << endl;

    s1->init(1001, 12, "XiaoMing");
    cout << *s1 << endl;
    
    return 0;
}




