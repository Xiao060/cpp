#include "find_word.hh"

int main(int argc, char *argv[]) {
    string queryWord("has");

    TextQuery tq;
    tq.readFile("china_daily.txt");
    tq.query(queryWord);            

    return 0;
} 





