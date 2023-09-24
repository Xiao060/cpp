#include <fstream>
#include <iostream>
#include "query.hh"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;




int main(int argc, char* argv[]) {

    ifstream ifs("The_Holy_Bible.txt");

    runQueries(ifs);
    
    ifs.close();

    return 0;
}




