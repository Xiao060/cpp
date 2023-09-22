#include <cstring>
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;


class Person {
public:
    Person(const char* name, int age)
    : _name(new char[strlen(name) + 1]())
    , _age(age) {
        strcpy(_name, name);
    }

    ~Person() {
        delete [] _name;
    }

    void display() {
        cout << "name: " << _name << endl 
             << "age: " << _age << endl;
    }

private:
    char* _name;
    int _age;
};

class Employee 
: public Person {

public:
    Employee(const char* name, int age, int department, int salary) 
    : Person(name, age)
    , _department(department)
    , _salary(salary) {

        _totalSalary += _salary;
        ++_totalNum;
    }

    Employee(const Employee& rhs) 
    : Person(rhs)
    , _department(rhs._department)
    , _salary(rhs._salary) {

        _totalSalary += _salary;
        ++_totalNum;
    }
    
    ~Employee() {
        _totalSalary -= _salary;
        --_totalNum;
    }

    void display() {
        Person::display();
        cout << "department: " << _department << endl
             << "salary: " << _salary << endl;
    }

    // TODO:
    // 自复制, 需要修改 Person 部分 
    Employee& operator=(const Employee& rhs) {
        // 显式调用 基类的 赋值运算符函数
        Person::operator=(rhs);

        _totalSalary -= _salary;

        _salary = rhs._salary;
        _department = rhs._department;

        _totalSalary += _salary;
        return *this;
    }


    // 静态成员函数
    static double aveSalary() {
        return _totalSalary / _totalNum;
    }

private:
    int _department;
    int _salary;
    static double _totalSalary;
    static int _totalNum;
};

double Employee::_totalSalary = 0;
int Employee::_totalNum = 0;


int main(int argc, char* argv[]) {

    Employee a("XiaoMing", 23, 1, 3000);
    a.display();
    cout << endl;
    
    Employee b("XiaoHong", 22, 3, 4000);
    b.display();
    cout << endl;
    
    Employee c("XiaoGang", 35, 8, 7000);
    c.display();
    cout << endl;

    cout << "average: " << Employee::aveSalary() << endl;

    return 0;
}




