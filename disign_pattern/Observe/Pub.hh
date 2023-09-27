#ifndef __PUB_HPP__
#define __PUB_HPP__

#include "Publish_Subscribe.hh"
#include <string>


using std::string;

class Pub 
: public Publish {

public:

    Pub(int no, string name, char gender);

    void setinfo(int no, string name, char gender);
    
    
protected:
    
    
private:
    int _no;
    string _name;
    char _gender; 
};

#endif
