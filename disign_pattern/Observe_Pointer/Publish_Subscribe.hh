#ifndef __PUBLISH_SUBSCRIBE_HPP__
#define __PUBLISH_SUBSCRIBE_HPP__

#include <memory>
#include <set>
#include <iostream>

using std::set;
using std::shared_ptr;


// 前向声明
class Subscribe;

/****************************************************/
/*                  Publish                         */
/****************************************************/

class Publish {

public:
    friend class Subscribe;

protected:
    void attach(Subscribe* pSub);
    void detach(Subscribe* pSub);
    void notifySubscribe();
    
private:
    set<Subscribe*> _pObservers;
};



/****************************************************/
/*                  Subscribe                       */
/****************************************************/

class Subscribe {

public:

    friend class Publish;    

    Subscribe(Publish& pub) 
    : _pPub(&pub) {
        _pPub->attach(this);        
    }
    
    ~Subscribe() {
        _pPub->detach(this);
    }

protected:
    virtual void update() = 0;
    
private:
    Publish* _pPub;
};







#endif

