#include <cstdio>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::clog;

void printStreamStatus(std::istream& is);
void test2();
void test3();
void test4();
void test5();
void test6();



int main(void) {

    // test2();
    // test3();
    // test4();
    // test5();
    test6();

    return 0;
}

void printStreamStatus(std::istream& is) {

    // 默认 goodbit 置位(为 1)
    cout << "is.good() = " << is.good() << endl;
    cout << "is.bad() = " << is.bad() << endl;
    cout << "is.fail() = " << is.fail() << endl;
    cout << "is.eof() = " << is.eof() << endl;
}

void test2() {
    printStreamStatus(cin);

    // 若输入非整数内容, 则 failbit 置位
    int value;
    while (cin >> value) {
        cout << value << endl;
    }
    printStreamStatus(cin);

    // 无参数 clear 会复位所有错误标志位(重置流的状态)
    cin.clear();
    printStreamStatus(cin);

    // 将输入流中的 前n个字符忽略 或 将 delim及之前的所有字符忽略
    cin.ignore(1024, '\n');

    string s;
    cin >> s;
    cout << s << endl;
}

void test3() {
    int value;

    // 逗号表达式, 从左往右计算, 并以 最后一个表达式的值 作为 整个表达式的值
    while (cin >> value, !cin.eof()) {
        if (cin.bad()) {
            throw std::runtime_error("IO stream is corrupted!");
        }

        if (cin.fail()) {
            cerr << "bad data, pls input a valid integer number!" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
            continue;
        }

        cout << "value = " << value << endl;
    }
}

// getline() 获取一行输入
void test4() {
    char buffer[1024] = {0};
    cout << "pls input a line string: ";
    cin.getline(buffer, 1024);
    cout << "the line is: " << buffer << endl;
}

void test5() {
    // 往输出流写入一个字符
    cout.put('a');
    cout.put('\n');

    // 将 s 中的字符写入 输出流, 写入长度为 n
    char str[] = "hello, world!";
    cout.write(str, sizeof(str));

    // win 采用小端存储, 即 64 63 62 61, 十进制为 100 99 98 97
    // 将 int* 强转为 char* 则 会将其当成 4 个字母 d c b a
    int x = 0x61626364;
    cout.write((char*) &x, sizeof(x)) << endl;
}

void test6() {

    // cout 写入的文件描述符为 1
    cout << "Hello, cout!" << endl;

    // cerr / clog 写入的文件描述符为 2
    // cerr 为无缓冲
    // clog 为有缓冲, but 缓冲区大小默认为 0, 效果与无缓冲相同, 
    // 可以通过 setbuf 设置缓冲区大小
    // setbuf(FILE *__restrict stream, char *__restrict buf)
    
    cerr << "Hello, cerr1!";
    sleep(1);
    cerr << "Hello, cerr2!" << endl;
    
    sleep(3);
    
    clog << "Hello, clog1!";
    sleep(1);
    clog << "Hello, clog2!" << endl;

    sleep(3);
    cout << "Hello ";
    sleep(1);
    cout << "World!" << endl;
}