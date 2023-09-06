#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::cerr;

void printStreamStatus(std::istream& is);
void test2();
void test3();



int main(int argc, char* argv[]) {

    // test2();
    test3();

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