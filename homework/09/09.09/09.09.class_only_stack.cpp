#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

// 只能生成栈对象, 即 new delete 私有
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

    ~Student() {
        if (_name) {
            delete [] _name;
            _name = nullptr;
        }
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

    void print() {
        cout << "num: " << _num << endl
             << "age: " << _age << endl
             << "name: " << _name  << endl;
    }

private:
    void* operator new(size_t sz) {
        return malloc(sz);
    }

    void operator delete(void *p) {
        free(p);
    }

    int _num;
    char* _name;
    int _age;
};


int main(int argc, char* argv[]) {

    Student s1(1001, "XiaoMing", 12);
    s1.print();

    Student s2(s1);
    s2.print();

    Student s3(1002, "XiaoHong", 11);
    s3.print();

    s2 = s3;
    s2.print();

    return 0;
}




