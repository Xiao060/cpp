#include <iostream>
#include <string>
#include <regex>

using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::string;




int main(int argc, char* argv[]) {

    string a = "<abc>def<ghi>";
    regex e("<.*>");

    std::regex_search(a, e);
    

    return 0;
}




