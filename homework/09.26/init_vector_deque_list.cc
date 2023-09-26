#include <iostream>
#include <deque>
#include <list>
#include <vector>

using std::cout;
using std::endl;

using std::vector;
using std::deque;
using std::list;

template <typename T>
void display(T t) {

    auto it = t.begin();

    for ( ; it != t.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {

    // 1. 无参
    vector<int> vec1;
    display(vec1);

    deque<int> deq1;
    display(deq1);

    list<int> lst1;
    display(lst1);

    cout << "+++++++++++++++++++++++++" << endl;
    // 2. count 个 value

    vector<int> vec2(7, 8);
    display(vec2);

    deque<int> deq2(8, 5);
    display(deq2);

    list<int> lst2(9, 3);
    display(lst2);

    cout << "+++++++++++++++++++++++++" << endl;
    // 3. 迭代器范围

    vector<int> vec3(lst2.begin(), lst2.end());
    display(vec3);

    deque<int> deq3(vec2.begin(), vec2.end());
    display(deq3);

    list<int> lst3(deq2.begin(), deq2.end());
    display(lst3) ;

    cout << "+++++++++++++++++++++++++" << endl;
    // 4. 拷贝/移动 构造

    vector<int> vec4(vec3);
    display(vec3);
    display(vec4);
    
    deque<int> deq4(std::move(deq3));
    display(deq3);
    display(deq4);
        
    list<int> lst4(std::move(lst3));
    display(lst3);
    display(lst4);

    cout << "+++++++++++++++++++++++++" << endl;
    // 5. 大括号

    vector<int> vec5 = {2, 6, 8, 1, 4, 0};
    display(vec5);

    deque<int> deq5 = {6, 8, 2, 1, 4, 0};
    display(deq5);

    list<int> lst5 = {2, 4, 6, 8, 1, 0};
    display(lst5);

    return 0;
}




