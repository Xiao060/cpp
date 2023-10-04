#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

void test()
{
    vector<int> vec;//vec.reserve(2);
    vec.push_back(10);
    vec.push_back(20);
    // vec.push_back(30);

    bool flag = true;
    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << "  ";
        if(flag)
        {
            vec.push_back(30);//底层发生了扩容,会导致迭代器失效
            flag = false;
            it = vec.begin();
        }
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

// 