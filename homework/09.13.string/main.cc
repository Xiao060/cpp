#include <iostream>
#include <ostream>
#include "string.hh"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    String s1;
    cout << s1 << endl;

    
    // 此处使用 String s2 = "Hello World!" 也可以
    // but 此种方式 本质为 隐式转换, 表层视为构造函数的调用
    // 将 "H..." 转换为 一个 String 临时对象, 然后 使用拷贝构造复制给 s2
    String s2("Hello World!");
    cout << s2 << endl;

    String s3(s2);
    cout << s3 << endl;

    s1 = s2;
    cout << s1 << endl;

    s3 = "Hello C++!";
    cout << s3 << endl;

    s3 += s2;
    cout << s3 << endl;

    s1 += "How are you?";
    cout << s1 << endl;

    s1 += "";
    cout << s1 << endl;

    cout << s1[4] << endl;
    s1[4] = 'e';
    cout << s1 << endl;

    cout << s1.size() << endl;

    // cin >> s1;
    // cout << s1 << endl;

    
    String s5("bba");
    String s6("bca");
    String s7("bba");

    cout << "s5 < s6: " << (s5 < s6) << endl;
    cout << "s5 <= s6: " << (s5 <= s6) << endl;
    cout << "s5 > s6: " << (s5 > s6) << endl;
    cout << "s5 >= s6: " << (s5 >= s6) << endl;
    cout << "s5 == s6: " << (s5 == s6) << endl;
    cout << "s5 != s6: " << (s5 != s6) << endl;

    cout << "s5 < s7: " << (s5 < s7) << endl;
    cout << "s5 <= s7: " << (s5 <= s7) << endl;
    cout << "s5 > s7: " << (s5 > s7) << endl;
    cout << "s5 >= s7: " << (s5 >= s7) << endl;
    cout << "s5 == s7: " << (s5 == s7) << endl;
    cout << "s5 != s7: " << (s5 != s7) << endl;

    cout << "s1: " << s1 << endl;
    cout << "s3: " << s3 << endl;

    String s8 = s1 + s3;
    cout << "s8: " << s8 << endl;

    String s9 = s1 + "xxxxx";
    cout << "s9: " << s9 << endl;

    String s10 = "aaaaa" + s1;
    cout << "s10: " << s10 << endl;

    return 0;
}




