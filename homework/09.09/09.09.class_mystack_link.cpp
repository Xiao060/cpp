#include <iostream>

using std::cout;
using std::endl;

typedef struct node_s {
    int data;
    struct node_s* next;
} node_t;

class Stack {
public:
    Stack();
    ~Stack();
	bool empty();	//判断栈是否为空
	// bool full();	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int top();		//获取栈顶元素
    void print();
private:
    node_t* _node;
};

Stack::Stack() 
: _node(nullptr) {}

bool Stack::empty() {
    if (_node == nullptr) {
        return true;
    }
    return false;
}

Stack::~Stack() {
    node_t* temp = _node;
    while (temp) {
        _node = temp->next;
        free(temp);
        temp = _node;
    }
}

void Stack::push(int n) {
    node_t* temp = new node_t();
    temp->data = n;
    temp->next = _node;

    _node = temp;
}

void Stack::pop() {
    node_t* temp = _node;

    _node = temp->next;
    delete temp;
}

void Stack::print() {
    node_t* temp = _node;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int Stack::top() {
    return _node->data;
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




