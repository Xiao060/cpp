#include <iostream>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;
using std::copy;

template<typename T>
class Vector
{
public:
    typedef T* iterator;

    iterator begin()
    {
	  return _start;
    }

    iterator end()
    {
	  return _finish;
    }

    Vector()
    : _start(nullptr)
    , _finish(nullptr)
    , _end_of_storage(nullptr)
    {

    }

    ~Vector();

    void push_back(const T &); 
    void pop_back();    

    int size() const;
    int capacity() const;
private:
    void reallocate();//重新分配内存,动态扩容要用的
private:    
    static std::allocator<T> _alloc;

    T * _start;   //指向数组中的第一个元素
    T * _finish;  //指向最后一个实际元素之后的那个元素
    T * _end_of_storage; //指向数组本身之后的位置
};

//静态数据成员的初始化
template <typename T>
std::allocator<T> Vector<T>::_alloc;

template <typename T>
Vector<T>::~Vector()
{
    if(_start)
    {
        while(_start != _finish)
        {
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, capacity());
    }
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    /* if(_finish == _end_of_storage) */
    if(size() == capacity())
    {
        //需要进行扩容
        reallocate();
    }

    if(size() < capacity())
    {
        //构建对象
        _alloc.construct(_finish++, value);
        /* ++_finish; */
    }
}

template <typename T>
void Vector<T>::pop_back()
{
    if(size() > 0)
    {
        //销毁对象
        _alloc.destroy(--_finish);
    }
}

template <typename T>
int Vector<T>::size() const
{
    return _finish - _start;
}

template <typename T>
int Vector<T>::capacity() const
{
    return _end_of_storage - _start;
}

template <typename T>
void Vector<T>::reallocate()
{
    //1、申请空间
    //1.1、如何得到老的空间与新的空间
    int oldCapacity =  capacity();
    int newCapacity = 2 * oldCapacity > 0 ? 2 * oldCapacity : 1;
    //1.2、申请新空间
    /* _start = _alloc.allocate(newCapacity);//error */
    T *ptmp  = _alloc.allocate(newCapacity);//ok

    if(_start)
    {
        //2、将老的空间上的元素拷贝到新的空间来
        /* copy(_start, _finish, ptmp); */
        // std::uninitialized_copy(_start, _finish, ptmp);
        std::copy(_start, _finish, ptmp);
        
        cout << *_start << endl;
        cout << *ptmp << endl;


        //3、将老的空间上的元素销毁并且将空间回收
        while(_start != _finish)
        {
            //3.1、将老的空间上的元素销毁
            /* _alloc.destroy(_start++); */
            _alloc.destroy(--_finish);
        }
        //3.2、将老的空间进行回收
        _alloc.deallocate(_start, oldCapacity);
    }
    //4、最后将三个指针与新的空间之间产生关系
    _start = ptmp;
    _finish = ptmp + oldCapacity;
    _end_of_storage = ptmp + newCapacity;
}

void printCapacity(const Vector<int> &con)
{
    cout << "con.size() = " << con.size() << endl;
    cout << "con.capacity() = " << con.capacity() << endl;
}

void test()
{
    Vector<int> vec;
    printCapacity(vec);

    cout << endl;
    vec.push_back(1);
    printCapacity(vec);

    cout << endl;
    vec.push_back(2);
    printCapacity(vec);

    cout << endl;
    vec.push_back(3);
    printCapacity(vec);

    cout << endl;
    vec.push_back(4);
    printCapacity(vec);

    cout << endl;
    vec.push_back(5);
    printCapacity(vec);

    cout << endl;
    vec.push_back(6);
    printCapacity(vec);

    cout << endl;
    vec.push_back(7);
    printCapacity(vec);

    cout << endl;
    vec.push_back(8);
    printCapacity(vec);

    cout << endl;
    vec.push_back(5);
    printCapacity(vec);

    cout << endl;
    for(auto &elem : vec)
    {
        cout << elem << "  ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

