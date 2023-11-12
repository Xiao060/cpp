#include <iostream>
#include <string>
#include <unistd.h>
#include <crypt.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;



int main(int argc, char* argv[]) {

    string passwd = "xiao060";
    string salt = "2iOt7nhEkwS23GEH";
    // string salt = "12345678";
    string encodedPasswd = crypt(passwd.c_str(), salt.c_str());
    cout << encodedPasswd << endl;

    return 0;
}




