#include <iostream>

#include "pubsub.h"

using namespace std;

int main() {

    bool changed=false;

    string key="Testing";
    string value="123";

    pubsub *ps = new pubsub();

//    ps->display();

    changed=ps->set(key.c_str(), value.c_str());

    if(changed) {
        cout << "changed 1:" << key << " " << value << endl;
    }
    // 
    // If c is true the definition changed.
    // We can decide here if we want to do anything about it.
    //
//    ps->display();

    changed=ps->set(key.c_str(), value.c_str());

    if(changed) {
        cout << "changed 2:" << key << " " << value << endl;
    }

    key = "Testing";
    value = "again";

    changed=ps->set(key.c_str(), value.c_str());

    if(changed) {
        cout << "changed 3:" << key << " " << value << endl;
    }
//    ps->display();

    bool found;
    string def;

    tie(found, def) = ps->get((char *)"Test");

    cout << "Found    : " << found << endl;
    cout << "Value    : " << def << endl;

    tie(found, def) = ps->get((char *)"Bill");

    cout << "Found    : " << found << endl;
    cout << "Value    : " << def << endl;
}
