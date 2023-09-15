#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

class Student {

public:
    // 构造函数
    Student(int num = 0, const char* name = "", int age = 0)
    : _num(num)
    , _name(new char[strlen(name) + 1]())
    , _age(age) {
        strcpy(_name, name);
    }

    // 拷贝构造函数
    Student(const Student& stu) 
    : _num(stu._num)
    , _name(new char[strlen(stu._name) + 1]())
    , _age(stu._age) {
        strcpy(_name, stu._name);
    }

    // 析构函数
    ~Student() {
        delete [] _name;
    }

    // 重载 赋值运算符
    Student& operator=(const Student& stu) {
        if (this != &stu) {
            delete [] _name;
            _num = stu._num;
            _name = new char[strlen(stu._name) + 1]();
            strcpy(_name, stu._name);
            _age = stu._age;
        }
    
        return *this;
    }

    void print(void) {
        // printf("%p\n", this);
        cout << "num: " << _num << endl
             << "name: " << _name << endl 
             << "age: " << _age << endl << endl;
    }

private:
    int _num;
    char* _name;
    int _age;
};


int main(int argc, char* argv[]) {

    Student s1;
    // printf("%p\n", &s1);
    s1.print();

    Student s2(1326, "XiaoMing", 12);
    s2.print();

    // 拷贝构造
    Student s3 = s2;
    s3.print();

    // 重载 =
    Student s4;
    s4 = s2;
    s4.print();

    Student* s5 = new Student(1327, "XiaoHong", 12);
    s5->print();
    delete s5;

    return 0;
}




