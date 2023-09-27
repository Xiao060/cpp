#include "Sub.hh"
#include "Publish_Subscribe.hh"


Sub::Sub(Publish& pub, int id) 
: Subscribe(pub) 
, _id(id) { }


void Sub::update() {
    cout << "subid = " << _id << ", received!" << endl;
}