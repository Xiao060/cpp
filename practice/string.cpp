#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

    char p[] = "Hello World!";
    
    // 对于数组来说, 数组名表示的是 数组首元素的地址
    // 数组名 + 1 表示的是数组 第2个 元素的地址
    // 例: p 的类型为 char*, p + 1 类型也为 char* 
    cout << "p, p+1\n";
    printf("%p\n", p);
    printf("%p\n\n", p + 1);

    // 对于数组来说, 数组名取地址表示的是 整个数组的 起始地址
    // 数组名取地址 + 1 表示的是 整个数组后 另一个数组 的起始地址
    // 例: &p 类型为 char(*)[12], &p + 1 类型也为 char(*)[12] 
    cout << "&p, &p+1\n";
    cout << &p << endl;
    cout << &p + 1 << endl;    


    // string str = p; 
    string str = "Hello World!";
    // string str("Hello World!");

    // string 取值, 下标操作符 [], 不会索引越界, 引发未定义行为
    cout << str[11] << endl;
    // string 取值, 函数 at(), 索引越界, 抛出 std::out_of_range 异常
    cout << str.at(6) << endl;

    // 正向迭代器, 类型为 ::iterator
    // begin() 返回 指向容器中第一个元素的 迭代器
    // end() 返回 指向容器中最后元素后面位置的迭代器
    string::iterator i;
    for (i = str.begin(); i < str.end(); ++i) {
        cout << *i << " ";
    }
    cout << endl;

    // 反向迭代器, 注意 即使为 反向迭代器, for 循环时任然是 ++
    // rbegin() 返回 指向容器中最后一个元素的迭代器
    // rend() 返回 指向容器中第一个元素前面位置的迭代器
    string::reverse_iterator j;
    for (j = str.rbegin(); j < str.rend(); ++j) {
        cout << *j << " ";
    }
    cout << endl;


    // 判断字符串是否为空, 空返回 1, 非空返回 0
    cout << str.empty() << endl;
    string s = "";
    cout << s.empty() << endl;


    cout << str.length() << endl;
    cout << str.size() << endl;
    // 返回 string 容量, 一般 按照 n*16-1 分配, 但是此 os 最低分配 15, 之后递增
    cout << str.capacity() << endl;
    cout << str.max_size() << endl;

    
    string yy = "6789";
    
    // 追加 n 个字符 c
    str.append(2, '?');
    cout << str << endl;
    // 追加 另一个字符串 
    str.append("1234");
    cout << str << endl;
    // char* 参数: 追加 另一字符串的前 n 个字符
    str.append("mnpq", 2);
    cout << str << endl;
    // string 参数: 追加 另一个字符串 从 pos 开始的所有内容
    str.append(yy, 2);
    // 追加 另一个字符串的一部分, 后两个参数为 起始索引 / 长度
    str.append("abcd", 1, 2);
    cout << str << endl;

    // 获取 str 从 pos 开始, 长度为 n 的子串
    string tmp = str.substr(3, 5);
    cout << tmp << endl;

    
    // 删除 从 pos 开始, 长度为 len 的内容
    str.erase(3, 5);
    cout << str << endl;
    // 删除 迭代器指向的字符
    string::iterator t = str.begin() + 6;
    str.erase(t);
    cout << str << endl;
    // 删除 迭代器 [start, end) 间的所有字符
    string::iterator start = str.begin() + 2;
    string::iterator end = str.end() - 5;
    str.erase(start, end);
    cout << str << endl;

    // 清空字符串
    str.clear();
    cout << str << endl;

    return 0;
}




