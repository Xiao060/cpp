#include "self_vector.hh"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <streambuf>

using std::copy;

template<typename T>
Vector<T>::Vector() 
: _start(nullptr)
, _finish(nullptr)
, _end_of_storage(nullptr) { }

template<typename T>
Vector<T>::~Vector() {

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
    // TODO: 判断空
    --_finish;
    _alloc.destory(_finish);
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

    size_t old_size = size();
    size_t new_size = old_size == 0 ? 1 : 2 * old_size;

    auto new_start = _alloc.allocate(old_size);
    auto new_finish = new_start;
    new_finish = copy(_start, _finish, new_start);

    _alloc.destory(_start, _finish);
    _alloc.deallocate(_start, capacity());

    _start = new_start;
    _finish = new_finish;
    _end_of_storage = new_start + new_size;
}