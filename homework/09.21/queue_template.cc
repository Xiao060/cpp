#include <iostream>

using std::cout;
using std::endl;

template <typename T = int, size_t sz = 10>
class Queue {
public: 
    Queue() 
    : _data(new T[sz]()) 
    , _front(0) 
    , _rear(0) 
    , _size(0) {}

    ~Queue() {
        delete [] _data;
    }

    bool is_empty() const;
    bool is_full() const;
    int size() const;
    int enqueue(const T&);
    int dequeue();
    T front() const;
    T back() const;

private:
    T* _data;
    int _front;
    int _rear;
    int _size;
};

template <typename T, size_t sz>
bool Queue<T, sz>::is_empty() const {
    return _size == 0;
}

template <typename T, size_t sz>
bool Queue<T, sz>::is_full() const {
    return _size == sz;
}

template <typename T, size_t sz>
int Queue<T, sz>::size() const {
    return _size;
}

template <typename T, size_t sz>
int Queue<T, sz>::enqueue(const T& rhs) {
    if (!is_full()) {
        _data[_rear++] = rhs;
        ++_size;
        return 0;
    }

    cout << "Error: the queue is full!" << endl;
    return 1;
}

template <typename T, size_t sz>
int Queue<T, sz>::dequeue() {
    if (!is_empty()) {
        ++_front;
        --_size;
        return 0;
    }

    cout << "Error: the queue is empty!" << endl;
    return 1;
}

template <typename T, size_t sz>
T Queue<T, sz>::front() const {
    if (!is_empty()) {
        return _data[_front];
    }

    cout << "Error: the queue is empty!" << endl;
    return (T) 1;
}

template <typename T, size_t sz>
T Queue<T, sz>::back() const {
    if (!is_empty()) {
        return _data[_rear];
    }

    cout << "Error: the queue is empty!" << endl;
    return (T) 1;
}


int main(int argc, char* argv[]) {

    Queue<int, 5> q1;

    cout << q1.is_empty() << endl;
    cout << q1.is_full() << endl;
    q1.dequeue();
    q1.front();

    cout << "****************************************" << endl;

    for (int i = 0; i < 7; ++i) {
        cout << i << endl;
        q1.enqueue(i);
    }
    cout << q1.is_empty() << endl;
    cout << q1.is_full() << endl;

    cout << "****************************************" << endl;

    while (!q1.is_empty()) {
        cout << q1.front() << endl;
        q1.dequeue();
    }
    cout << q1.is_empty() << endl;
    cout << q1.is_full() << endl;

    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;

    Queue<char, 10> q2;

    for (int i = 0; i < 12; ++i) {
        cout << char('a' + i) << endl;
        q2.enqueue('a' + i);
    }

    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
    
    while (!q2.is_empty()) {
        cout << q2.front() << endl;
        q2.dequeue();
    }

    cout << "++++++++++++++++++++++++++++++++++++++++" << endl;

    return 0;
}




