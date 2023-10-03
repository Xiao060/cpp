#include <iterator>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include <streambuf>
#include <iostream>

using std::cout;
using std::endl;
using std::copy;
using std::allocator;
using std::ostream_iterator;
using std::copy;

template<typename T>
class Vector {
public:   
    Vector();     
    ~Vector();          
    void push_back(const T &);      
    void pop_back();         
    int size();     
    int capacity(); 
    T* begin() { return _start; }
    T* end() {return _finish; }

private:     
    void reallocate();//重新分配内存,动态扩容要用的

private:         
    static std::allocator<T> _alloc;          
    T* _start;                 //指向数组中的第一个元素     
    T* _finish;                //指向最后一个实际元素之后的那个元素     
    T* _end_of_storage;        //指向数组本身之后的位置 
};




template<typename T>
Vector<T>::Vector() 
: _start(nullptr)
, _finish(nullptr)
, _end_of_storage(nullptr) { }

template<typename T>
Vector<T>::~Vector() {
    if (_start != nullptr) {
        _alloc.destroy(_start);
        _alloc.deallocate(_start, capacity());
    }
}

template<typename T>
void Vector<T>::push_back(const T& rhs) {
    if (_finish == _end_of_storage) {
        reallocate();
    }

    _alloc.construct(_finish, rhs);
    ++_finish;
}

template<typename T>
void Vector<T>::pop_back() {
    // 判断非空
    if (size() > 0) {
        --_finish;
        _alloc.destory(_finish);
    }
}

template<typename T>
int Vector<T>::size() {
    return _finish - _start; 
}

template<typename T>
int Vector<T>::capacity() {
    return _end_of_storage - _start;
}

//重新分配内存,动态扩容要用的 
template<typename T>
void Vector<T>::reallocate() {

    // 1.申请空间
    size_t old_capacity = capacity();
    size_t new_capacity = old_capacity == 0 ? 1 : 2 * old_capacity;
    auto new_start = _alloc.allocate(new_capacity);

    if (_start) {
        // 2.将老的空间上的元素拷贝到新的空间来
        auto new_finish = copy(_start, _finish, new_start);

        // 3.将老的空间上的元素循环销毁并且将空间回收
        // 此处 从后往前销毁, 目的是 为了方便后续 空间回收
        while (_start != _finish) {
            --_finish;
            _alloc.destroy(_finish);
        }

        _alloc.deallocate(_start, capacity());
    }
    
    // 4.最后将三个指针与新的空间之间产生关系
    _start = new_start;
    _finish = _start + new_capacity;
    _end_of_storage = new_start + new_capacity;
}


template <class T>
std::allocator<T> Vector<T>::_alloc;

int main(int argc, char* argv[]) {

    ostream_iterator<int> osi(cout, " ");

    Vector<int> vec;
    cout << vec.size() << " " << vec.capacity() << endl;
    copy(vec.begin(), vec.end(), osi);
    cout << endl;


    vec.push_back(23);
    cout << vec.size() << " " << vec.capacity() << endl;
    copy(vec.begin(), vec.end(), osi);
    cout << endl;

    vec.push_back(45);
    cout << vec.size() << " " << vec.capacity() << endl;
    copy(vec.begin(), vec.end(), osi);
    cout << endl;

    vec.push_back(32);
    cout << vec.size() << " " << vec.capacity() << endl;
    copy(vec.begin(), vec.end(), osi);
    cout << endl;

    vec.push_back(29);
    cout << vec.size() << " " << vec.capacity() << endl;
    copy(vec.begin(), vec.end(), osi);
    cout << endl;

    return 0;
}
