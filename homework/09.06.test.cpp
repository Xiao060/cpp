#include <iostream>

using std::cin;
using std::cout;
using std::endl;


/*
class Sample {
	int i;
public:
	Sample();
	Sample(int val);
	void Display();
	~Sample();
};

Sample::Sample() {
    cout << "Constructor1" << endl;
    i=0;
}

Sample::Sample(int val) {
    cout << "Constructor2" << endl;
    i=val;
}

void Sample::Display() {
    cout << "i=" << i << endl;
}

Sample::~Sample() {
    cout << "Destructor" << endl;
}

int main() {
    Sample a, b(10);
    a.Display();
    b.Display();
	 
    return 0;
}
*/


/*
class Test {
public: 
    Test(char c) {
        _name = c;
    }

    ~Test() {
        cout << "Destructor " << _name << endl;
    }

private:
    char _name;
};

Test C('C');					    // 全局
int main() {
    Test *A = new Test('A');
    Test B('B');
    static Test D('D');			// 静态
    delete A;

    return 0;
}
*/

/*
struct Foo {
	Foo(){ }
	Foo(int){ }
	void fun(){ }
};

int main(void) {
	Foo a(10);  //语句1
	a.fun();    //语句2
	Foo b;    //语句3
	b.fun();    //语句4 
	return 0;
}
*/



