#include <iostream>
#include <ostream>
#include <fstream>
#include "CowString.hh"

using std::ofstream;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    // CowString s1;
    // cout << "s1: " << s1 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;

    // CowString s2 = s1;
    // cout << "s2: " << s2 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;
    // cout << "s2_num:" << s2.use_count() << endl;

    // cout << "**************************************************" << endl;

    // CowString s3 = "Hello World";
    // cout << "s3: " << s3 << endl;
    // cout << "s3_num:" << s3.use_count() << endl;
    // CowString s4 = s3;
    // cout << "s4: " << s4 << endl;
    // cout << "s4_num:" << s4.use_count() << endl;
    
    // cout << "**************************************************" << endl;

    // s2 = s3;
    // cout << "s1: " << s1 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;
    // cout << "s2: " << s2 << endl;
    // cout << "s2_num:" << s2.use_count() << endl;
    // cout << "s3: " << s3 << endl;
    // cout << "s3_num:" << s3.use_count() << endl;
    // cout << "s4: " << s4 << endl;
    // cout << "s4_num:" << s4.use_count() << endl;

    // cout << "**************************************************" << endl;

    // // 直接输出 自定义类型, 1.输出重载, 2.类型转换
    // cout << s2[0] << endl;

    // cout << "s1: " << s1 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;
    // cout << "s2: " << s2 << endl;
    // cout << "s2_num:" << s2.use_count() << endl;
    // cout << "s3: " << s3 << endl;
    // cout << "s3_num:" << s3.use_count() << endl;
    // cout << "s4: " << s4 << endl;
    // cout << "s4_num:" << s4.use_count() << endl;


    CowString s1 = "Hello World!";
    CowString s2 = s1;
    CowString s3;
    s3 = s2;
    cout << "s1: " << s1 << endl;
    cout << "s1_num:" << s1.use_count() << endl;
    cout << "s2: " << s2 << endl;
    cout << "s2_num:" << s2.use_count() << endl;
    cout << "s3: " << s3 << endl;
    cout << "s3_num:" << s3.use_count() << endl;

    cout << "**************************************************" << endl;

    // s3[2] = '?';
    // cout << "s1: " << s1 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;
    // cout << "s2: " << s2 << endl;
    // cout << "s2_num:" << s2.use_count() << endl;
    // cout << "s3: " << s3 << endl;
    // cout << "s3_num:" << s3.use_count() << endl;

    // s3 = "Hello C++!";
    // cout << "s1: " << s1 << endl;
    // cout << "s1_num:" << s1.use_count() << endl;
    // cout << "s2: " << s2 << endl;
    // cout << "s2_num:" << s2.use_count() << endl;
    // cout << "s3: " << s3 << endl;
    // cout << "s3_num:" << s3.use_count() << endl;

    s3[20];
    cout << s3[20] << endl;

    s3[20] = 'V';

    return 0;
}




