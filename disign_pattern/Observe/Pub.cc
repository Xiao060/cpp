#include "Pub.hh"

Pub::Pub(int no, string name, char gender) 
: _no(no)
, _name(name)
, _gender(gender) { }


void Pub::setinfo(int no, string name, char gender) {
    _no = no;
    _name = name;
    _gender = gender;

    notifySubscribe();
}