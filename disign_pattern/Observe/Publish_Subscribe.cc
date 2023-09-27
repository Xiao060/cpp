#include "Publish_Subscribe.hh"
#include <iostream>
#include <memory>

using std::shared_ptr;
using std::cout;
using std::endl;



/****************************************************/
/*                  Publish                         */
/****************************************************/

void Publish::attach(shared_ptr<Subscribe> spSub) {

    auto it = _Observers.insert(spSub);
    if (!it.second) {
        cout << "Error: attach failed!" << endl;
    } else {
        cout << "Attach success!" << endl;

        cout << it.first->use_count() << endl;
    }
}

void Publish::detach(shared_ptr<Subscribe> spSub) {
    auto it = _Observers.find(spSub);
    if (it != _Observers.end()) {
        cout << "Error: Subscribe is not exit!" << endl;
    } else {
        _Observers.erase(it);
        cout << "Detach success!" << endl;
    }
}

void Publish::notifySubscribe() {
    for (auto& elem : _Observers) {
        elem->update();
    }
}



/****************************************************/
/*                  Subscribe                       */
/****************************************************/
