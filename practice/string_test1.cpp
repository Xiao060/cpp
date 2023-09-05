#include <cstddef>
#include <iostream>
#include <string>
#include <variant>

// using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

    string s1 = "Hello";
    string s2 = "World";

    // 获取 str 长度, 返回值为 size_type(size_t)
    cout << s1.size() << endl;
    cout << s1.length() << endl;

    // 遍历字符串, 数组形式
    for (size_t i = 0; i < s1.size(); ++i) {
        cout << s1[i] << " ";
    }
    cout << endl;

    // 遍历字符串, 迭代器形式 
    string::iterator j;
    for (j = s2.begin(); j < s2.end(); ++j) {
        cout << *j << " ";
    }
    cout << endl;

    // str 拼接
    string s3 = s1 + " " + s2;
    cout << "s3: " << s3 << endl;

    // 在 s3 中查找子串出现的位置, 不存在则返回 string::npos
    size_t pos = s3.find("World");
    cout << "pos: " << pos << endl;
    cout << "npos: " << string::npos << endl;

    // substr(start, len) 从字符串中截取子串
    // 从 start 开始截取, 截取长度为 len;
    // 若 len > 可截取总长度 或 len省略, 则取到末尾 
    string substr = s3.substr(pos);
    cout << "substr: " << substr << endl;
    

    return 0;
}




