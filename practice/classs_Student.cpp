#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>

// using std::cin;
using std::cout;
using std::endl;

class Student {
public:
    Student(int id, const char* name) 
    : _id(id)
    , _name(new char[strlen(name) + 1]()) {
        strcpy(_name, name);
        cout << "Student()" << endl;
    }

    ~Student() {
        delete [] _name;
        cout << "~Student()" << endl;
    }

    void* operator new(size_t sz) {
        void* ret = malloc(sz);
        cout << "new" << endl;
        return ret;
    }
    
    void operator delete(void* pointer) {
        free(pointer);
        cout << "delete" << endl;
    }

    void print() const {
        cout << "id:" << _id << endl
             << "name:" << _name << endl;
    }

private:
    int _id;
    char* _name;
};


int main(int argc, char* argv[]) {

    Student* stu = new Student(100, "Jackie");
    stu->print();
    delete stu;

    return 0;
}




