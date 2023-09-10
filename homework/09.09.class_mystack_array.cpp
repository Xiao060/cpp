#include <iostream>

using std::cout;
using std::endl;

#define CAPACITY 20

class Stack {
public:
	bool empty();	//判断栈是否为空
	bool full();	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int top();		//获取栈顶元素
    void print();
private:
    int _data[CAPACITY] = {0};
    // _size 表示已储存的元素个数
    int _size = 0;
};

bool Stack::empty() {
    if (_size == 0) {
        return true;
    }
    return false;
}

bool Stack::full() {
    if (_size == CAPACITY) {
        return true;
    } else {
        return false;
    }
}

void Stack::push(int n) {
    _data[_size] = n;
    ++_size;
}

void Stack::pop() {
    --_size;
}

int Stack::top() {
    return _data[_size-1];
}

void Stack::print() {
    for (int i=0; i<_size; ++i) {
        cout << _data[i] << " ";
    }
    cout << endl;
}


int main(int argc, char* argv[]) {

    Stack s;

    for (int i=0; i < 10; ++i) {
        s.push(i);
    }

    while (!s.empty()) {
        cout << s.top() << endl;
        s.print();
        s.pop();
    }

    return 0;
}




