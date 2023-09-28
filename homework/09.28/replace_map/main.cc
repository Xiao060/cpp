#include "Replace.hh"
#include <iostream>



int main(int argc, char* argv[]) {

    Replace rep;

    rep.read_map("map.txt");
    rep.replace("file.txt");

    return 0;
}




