#include <iostream>

using std::cout;
using std::endl;

class Stack {
public:
    Stack(int capacity = 10)
    : _top(-1)
    , _capacity(capacity)
    , _data(new int[capacity]()) {}

    ~Stack() {
        if (_data) {
            delete [] _data;
            _data = nullptr;
        }
    }

	bool empty() const;	//判断栈是否为空
	bool full() const;	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int top() const;		//获取栈顶元素
    void print() ;

private:
    int* _data;
    int _capacity;
    int _top;
};

bool Stack::empty() const {
    return _top == -1;
}

bool Stack::full() const {
    return _top + 1 == _capacity;
}

void Stack::push(int num) {
    if (!full()) {
        _data[++_top] = num;
    } else {
        cout << "Stack is full!" << endl;
    }
}

void Stack::pop() {
    if (!empty()) {
        --_top;
    } else {
        cout << "Stack is empty!" << endl;
    }
}

int Stack::top() const {
    if (!empty()) {
        return _data[_top];
    } else {
        cout << "Stack is empty!" << endl;
        return 1;
    }
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




