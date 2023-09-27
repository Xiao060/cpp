#include "Publish_Subscribe.hh"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;



/****************************************************/
/*                  Publish                         */
/****************************************************/

void Publish::attach(Subscribe* pSub) {

    auto it = _pObservers.insert(pSub);
    if (!it.second) {
        cout << "Error: attach failed!" << endl;
    } else {
        cout << "Attach success!" << endl;
    }
}

void Publish::detach(Subscribe* pSub) {
    auto it = _pObservers.find(pSub);
    if (it == _pObservers.end()) {
        cout << "Error: Subscribe is not exit!" << endl;
    } else {
        _pObservers.erase(it);
        cout << "Detach success!" << endl;
    }
}

void Publish::notifySubscribe() {
    for (auto& elem : _pObservers) {
        elem->update();
    }
}



/****************************************************/
/*                  Subscribe                       */
/****************************************************/
