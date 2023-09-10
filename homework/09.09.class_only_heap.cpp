#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

// 堆对象的销毁需要用到 delete object;
// 第 1 步, 调用 析构函数 释放 数据成员申请的堆空间
// 第 2 步, 调用 operator delete 库函数(底层free), 回收对象自身所占的空间 
// 因此若只能生成堆对象, 需要将 析构函数 私有化
class Student {
public:
    Student(int num, const char* name, int age)
    : _num(num)
    , _name(new char[strlen(name) + 1]())
    , _age(age) {
        strcpy(_name, name);
    }

    Student(const Student& stu) 
    : _num(stu._num)
    , _name(new char[strlen(stu._name) + 1]())
    , _age(stu._age) {
        strcpy(_name, stu._name);
    }

    Student& operator=(const Student& stu) {
        if (this != &stu) {
            delete [] _name;
            _name = new char[strlen(stu._name) + 1]();
            strcpy(_name, stu._name);
            _num = stu._num;
            _age = stu._age;
        }

        return *this;
    }

    void destory() {
        delete this;
    }

    void print() {
        cout << "num: " << _num << endl
             << "age: " << _age << endl
             << "name: " << _name  << endl;
    }

private:
    ~Student() {
        if (_name) {
            delete [] _name;
            _name = nullptr;
        }
    }

    int _num;
    char* _name;
    int _age;
};


int main(int argc, char* argv[]) {

    Student * s1 = new Student(1001, "XiaoMing", 12);
    s1->print();

    Student* s2 = new Student(*s1);
    s2->print();

    Student* s3 = new Student(1002, "XiaoHong", 11);
    s3->print();

    *s2 = *s3;
    s2->print();

    s3->destory();
    s2->destory();
    s1->destory();

    return 0;
}




