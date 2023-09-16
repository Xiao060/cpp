#include <iostream>
#include "find_word.hh"

using std::cin;
using std::cout;
using std::endl;

//程序测试用例
int main(int argc, char *argv[]) {
    string queryWord("hello");

    TextQuery tq;
    tq.readFile("test.dat");
    tq.query(queryWord);
    return 0;
}




