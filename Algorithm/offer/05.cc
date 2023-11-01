/*
将一个字符串中的空格替换成 "%20"。

Input: "A B"

Output: "A%20B"
*/

/**
 * @param s string字符串 
 * @return string字符串
 */

#include <iostream>
#include <ostream>
using std::cout;
using std::endl;

char* replaceSpace(char* s ) {
    char* p = s;
    int n = 0;
    while (*p != '\0') {
        if (*p == ' ') {
            ++n;
        }
        ++p;
    }

    cout << "空格数量: " << n << endl;

    p += 2 * n;
    *p = '\0';
    --p;

    while (n > 0) {
        char tmp = *(p - 2 * n);

        if (tmp != ' ') {
            *p = tmp;
            --p;
        } else {
            *p = '0';
            --p;
            *p = '2';
            --p;
            *p = '%';
            --p;
        }
    }

    return 
}
