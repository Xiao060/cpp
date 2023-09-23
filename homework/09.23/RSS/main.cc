#include <iostream>
#include "rss.hh"

int main(int argc, char* argv[]) {

    RssReader rss;

    rss.parseRss();
    rss.dump("b.txt");

    return 0;
}




