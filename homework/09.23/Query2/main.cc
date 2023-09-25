#include "TextQuery.hh"
#include "QueryResult.hh"
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;



int main(int argc, char* argv[]) {

    ifstream ifs("The_Holy_Bible.txt");
    ofstream ofs1("a.txt");
    ofstream ofs2("b.txt");

    TextQuery text(ifs);
    text.printToFile(ofs1);

    QueryResult res = text.query("light");
    res.printToFile(ofs2);

    ofs2.close();
    ofs1.close();
    ifs.close();

    return 0;
}




