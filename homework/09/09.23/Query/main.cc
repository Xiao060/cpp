#include <fstream>
#include <iostream>
#include "query.hh"

using std::ifstream;
using std::cout;
using std::endl;


int main(int argc, char* argv[]) {

    ifstream ifs("The_Holy_Bible.txt");

    // runQueries(ifs);

    TextQuery t(ifs);
    
    Query p = ~Query("gold"); // | Query("light");

    print(cout, p.eval(t));

    ifs.close();

    return 0;
}




