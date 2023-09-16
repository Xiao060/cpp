#include "word_count.hh"
#include <iostream>


int main(int argc, char* argv[]) {
    Record test;

    test.read("The_Holy_Bible.txt");
    test.store("count.txt");
    
    return 0;
}




