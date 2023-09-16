#include <iostream>
#include "find_word.hh"


//程序测试用例
int main(int argc, char *argv[]) {
    string queryWord("has");

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);
    return 0;
}




