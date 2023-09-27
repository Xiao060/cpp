#ifndef __SUB_HPP__
#define __SUB_HPP__

#include "Publish_Subscribe.hh"
#include <iostream>
#include <ostream>

using std::cout;
using std::endl;

class Sub 
: Subscribe {

public:
    Sub(Publish& pub, int id);

    void update();
    
    
protected:
    
    
    
private:
    int _id; 
    
};

#endif
