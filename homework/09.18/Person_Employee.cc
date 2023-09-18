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
    , _salary(salary) {}

    void display() {
        Person::display();
        cout << "department: " << _department << endl
             << "salary: " << _salary << endl;
    }


private:
    int _department;
public:
    int _salary;
};


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
    
    double average = (a._salary + b._salary + c._salary) / 3.0;
    cout << "average salary: " << average << endl;

    return 0;
}




