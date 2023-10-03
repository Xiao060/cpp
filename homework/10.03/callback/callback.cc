#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::function;
using std::bind;

class Student {
public:
    Student(string name, int age)
    : _name(name)
    , _age(age) { }
    
    void showName() {
        cout << "My name is " << _name << "." << endl;
    }

    void showAge() {
        cout << "I'm " << _age << "years old." << endl;
    }

private:
    string _name;
    int _age;
};




class Show {
public:
    using ShowCallback = function<void()>;

    // 回调函数的注册
    void setShowNameCallback(ShowCallback&& cb) {
        _showNameCallback = std::move(cb);
    }

    void setShowAgeCallback(ShowCallback&& cb) {
        _showAgeCallback = std::move(cb);
    }


    // 回调函数的执行
    void handleShowNameCallback() const {
        if (_showNameCallback) {
            _showNameCallback();
        }
    }

    void handleShowAgeCallback() const {
        if (_showAgeCallback) {
            _showAgeCallback();
        }
    }
   
private:
    ShowCallback _showNameCallback;
    ShowCallback _showAgeCallback;
};



int main(int argc, char* argv[]) {

    Student s1("XiaoMing", 12);
    Student s2("XiaoHong", 13);

    Show show;


    // set...() 接收的参数 是 void() 的函数类型
    // 而 showName showAge 均含有一个参数 this 指针, 故此处使用 bind 进行绑定
    show.setShowNameCallback(bind(&Student::showName, &s1));
    show.setShowAgeCallback(bind(&Student::showAge, &s1));
    show.handleShowNameCallback();
    show.handleShowAgeCallback();

    show.setShowNameCallback(bind(&Student::showName, &s2));
    show.setShowAgeCallback(bind(&Student::showAge, &s2));
    show.handleShowNameCallback();
    show.handleShowAgeCallback();

    return 0;
}




