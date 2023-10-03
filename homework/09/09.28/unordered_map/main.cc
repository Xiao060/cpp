#include "Dictionary.hh"
#include <iostream>


int main(int argc, char* argv[]) {

    Dictionary dic;

    dic.read("The_Holy_Bible.txt");

    dic.store("a.txt");


    return 0;
}




