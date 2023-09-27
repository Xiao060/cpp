#ifndef __PUBLISH_SUBSCRIBE_HPP__
#define __PUBLISH_SUBSCRIBE_HPP__

#include <memory>
#include <set>

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
    void attach(shared_ptr<Subscribe> spSub);
    void detach(shared_ptr<Subscribe> spSub);
    void notifySubscribe();
    
private:
    set<shared_ptr<Subscribe>> _Observers;
};



/****************************************************/
/*                  Subscribe                       */
/****************************************************/

class Subscribe {

public:

    friend class Publish;    

    Subscribe(Publish& pub) {
        pub.attach(shared_ptr<Subscribe> (this));        
    }
    
protected:
    virtual void update() = 0;
    
private:
    // shared_ptr<Publish> _spPub;
};







#endif

