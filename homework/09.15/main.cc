#include <iostream>
#include "CowString.hh"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    CowString s1;
    cout << "s1: " << s1 << endl;
    cout << "s1_num:" << s1.use_count() << endl;

    CowString s2 = s1;
    cout << "s2: " << s2 << endl;
    cout << "s1_num:" << s1.use_count() << endl;
    cout << "s2_num:" << s2.use_count() << endl;

    cout << "**************************************************" << endl;

    CowString s3 = "Hello World";
    cout << "s3: " << s3 << endl;
    cout << "s3_num:" << s3.use_count() << endl;
    CowString s4 = s3;
    cout << "s4: " << s4 << endl;
    cout << "s4_num:" << s4.use_count() << endl;
    
    cout << "**************************************************" << endl;

    s2 = s3;
    cout << "s1: " << s1 << endl;
    cout << "s1_num:" << s1.use_count() << endl;
    cout << "s2: " << s2 << endl;
    cout << "s2_num:" << s2.use_count() << endl;
    cout << "s3: " << s3 << endl;
    cout << "s3_num:" << s3.use_count() << endl;
    cout << "s4: " << s4 << endl;
    cout << "s4_num:" << s4.use_count() << endl;


    return 0;
}




